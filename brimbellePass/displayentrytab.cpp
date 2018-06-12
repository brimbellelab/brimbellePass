// DisplayEntryTab.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "displayentrytab.h"

#include "account.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QVBoxLayout>

#include <iostream>

DisplayEntryTab::DisplayEntryTab(AccountsBook *accounts, QWidget *parent) : QWidget(parent)
{
    accountsBook = accounts;
    comboBoxAccountsList = new QComboBox(this);

    comboBoxAccountsList->addItems(accountsBook->getWebsiteList());

    QObject::connect(comboBoxAccountsList, SIGNAL(currentIndexChanged(const QString&)),
                     this, SLOT(reloadEntryContent(const QString&)));

    btnNewAccount = new QPushButton("New");
    btnNewAccount->setMaximumSize(40, 20);
    QObject::connect(btnNewAccount, SIGNAL(clicked()), this, SLOT(createAccount()));

    QHBoxLayout* accountsFieldLayout = new QHBoxLayout();
    accountsFieldLayout->addWidget(comboBoxAccountsList);
    accountsFieldLayout->addWidget(btnNewAccount);

    displayEntryContent = new DisplayEntryContent(this);

    btnSaveDatabase = new QPushButton("Save database");
    btnSaveAccount = new QPushButton("Save account");
    btnDeleteAccount = new QPushButton("Delete account");
    QObject::connect(btnSaveDatabase, SIGNAL(clicked()), this, SLOT(saveDatabase()));
    QObject::connect(btnSaveAccount, SIGNAL(clicked()), this, SLOT(saveAccount()));
    QObject::connect(btnDeleteAccount, SIGNAL(clicked()), this, SLOT(deleteAccount()));

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(btnSaveDatabase);
    buttonsLayout->addWidget(btnSaveAccount);
    buttonsLayout->addWidget(btnDeleteAccount);

    QVBoxLayout* verticalLayout = new QVBoxLayout();
    verticalLayout->addLayout(accountsFieldLayout);
    verticalLayout->addWidget(displayEntryContent);
    verticalLayout->addLayout(buttonsLayout);

    this->setLayout(verticalLayout);

    if (comboBoxAccountsList->count() > 0)
    {
        reloadEntryContent(comboBoxAccountsList->itemText(0));
    }
}



void
DisplayEntryTab::reloadEntryContent(const QString& text)
{
    if (text.isEmpty())
    {
        displayEntryContent->clearContent();
        return;
    }
    try
    {
        // This function can throw an error if the password is incorrect.
        displayEntryContent->update(accountsBook->getAccount(text.toStdString()));
    }
    catch (QString const& e)
    {
        // Something went wrong while deciphering a password. The ciphered string doesn't match the password!
        QMessageBox::warning(this, "Error", e);

        // Disable editable features as the password is incorrect.
        btnSaveDatabase->setEnabled(false);
        btnSaveAccount->setEnabled(false);
        btnDeleteAccount->setEnabled(false);
    }
    catch (std::string e)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(e));
    }
}



void
DisplayEntryTab::saveDatabase(void)
{
    QMessageBox::warning(this, "Oopsie", "It's not yet possible to save the database.");
}



void
DisplayEntryTab::saveAccount(void)
{
    uint32_t currentAccountKey = displayEntryContent->getCurrentAccountKey();
    Account* accountToSave  = new Account(currentAccountKey,
                                          comboBoxAccountsList->currentText().toStdString());
    try
    {
        displayEntryContent->saveChanges(*accountToSave);
    }
    catch (std::runtime_error re)
    {
        // No need to display a message box asking for the password again.
        QMessageBox::critical(this, "Error", re.what());

        // Something went wrong, accountToSave has not been correctly filled.
        delete accountToSave;
        return;
    }

    // If the new account is valid, remove the old one from accountBooks and delete it.
    // (it's actually a job for AccountsBook!)
    accountsBook->deleteAccount(currentAccountKey);

    // Add the new account to accountBooks;
    accountsBook->addAccount(accountToSave);

    // Update accountsList.
    comboBoxAccountsList->blockSignals(true); // Signals must be paused for a while or they're triggered when cleared.
    comboBoxAccountsList->clear();
    comboBoxAccountsList->addItems(accountsBook->getWebsiteList());

    // Reload Entry content.
    auto indexEntry = comboBoxAccountsList->findText(QString::fromStdString(accountToSave->getWebsite()));
    if (indexEntry < 0)
    {
        std::cout << "can't find the website in the list" << std::endl;
        // Account's website not found... Loading the first entry.
        indexEntry = 0;
    }
    std::cout << "Loading item " << indexEntry << std::endl;
    comboBoxAccountsList->blockSignals(false);
    comboBoxAccountsList->setCurrentIndex(indexEntry);
}



void
DisplayEntryTab::deleteAccount(void)
{
    uint32_t currentAccountKey = displayEntryContent->getCurrentAccountKey();

    if (QMessageBox::question(this, "Delete?", "Are you sure you want to delete this account?") == QMessageBox::No)
    {
        // Abort.
        return;
    }

    accountsBook->deleteAccount(currentAccountKey);

    // Remove entry from the combobox list.
    auto indexEntry = comboBoxAccountsList->currentIndex();

    if (comboBoxAccountsList->count() <= 1)
    {
        QMessageBox::warning(this, "", "Accounts list is empty.");
        comboBoxAccountsList->blockSignals(false);
        btnSaveAccount->setEnabled(false);
        btnDeleteAccount->setEnabled(false);
    }

    std::cout << "Loading item " << indexEntry << std::endl;
    comboBoxAccountsList->removeItem(indexEntry);
}



void
DisplayEntryTab::createAccount(void)
{
    // Ask for the account name.
    bool ok;
    QString newAccountName = QInputDialog::getText(this,
                                                   "Account name",
                                                   "Enter the new account name",
                                                   QLineEdit::Normal,
                                                   QString(),
                                                   &ok);
    if (!ok || newAccountName.isEmpty())
    {
        return;
    }
    // Make sure the account name isn't taken yet.

    accountsBook->addAccount(new Account(accountsBook->getAvailableKey(), newAccountName.toStdString()));
    comboBoxAccountsList->blockSignals(true);
    comboBoxAccountsList->addItem(newAccountName);
    displayEntryContent->clearContent();
    comboBoxAccountsList->setCurrentText(newAccountName);
    comboBoxAccountsList->blockSignals(false);
}
