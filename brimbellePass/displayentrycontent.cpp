// DisplayEntryContent.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "displayentrycontent.h"

#include <iostream>

#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>

using namespace std;

DisplayEntryContent::DisplayEntryContent(QWidget *parent) : QWidget(parent)
{
    // No panic, it's just for the demo. I'll add an input box to let the user enter the actual password.
    //cipherEngine.setPassword("GUEST");
    bool ok = false;
    cipherEngine.setPassword(QInputDialog::getText(this,
                                                   "Enter password",
                                                   "Enter the main user password",
                                                   QLineEdit::Password,
                                                   QString(),
                                                   &ok));

    lineEditWebsite = new QLineEdit("No account found");

    gbLogins = new QGroupBox("Logins", this);
    layoutLogins = new QVBoxLayout;
    gbLogins->setLayout(layoutLogins),

    gbCurrentPassword = new QGroupBox("Current password");
    entryLineCurrentPassword = new PasswordEntryLine("", this);
    btnNewPassword = new QPushButton("New password", this);
    QObject::connect(btnNewPassword, SIGNAL(clicked()), this, SLOT(changePassword()));
    QVBoxLayout *layoutCurrentPassword = new QVBoxLayout;
    layoutCurrentPassword->addWidget(entryLineCurrentPassword);
    layoutCurrentPassword->addWidget(btnNewPassword);
    layoutCurrentPassword->setMargin(defaultMargin);
    gbCurrentPassword->setLayout(layoutCurrentPassword);

    gbOldPasswords = new QGroupBox("Old passwords");
    layoutOldPasswords = new QVBoxLayout;
    layoutOldPasswords->setMargin(defaultMargin);
    gbOldPasswords->setLayout(layoutOldPasswords);

    gbSafetyQA = new QGroupBox("Safety questions");
    comboBoxSafetyQuestion = new QComboBox();
    comboBoxSafetyQuestion->addItems(currentAccount.getSafetyQuestions());
    safetyAnswer = new PasswordEntryLine("");
    if (comboBoxSafetyQuestion->count() > 0)
    {
        updateSafetyAnswerField(0); // Always point at the first item on creation.
    }
    QVBoxLayout *layoutSafetyQA = new QVBoxLayout;
    layoutSafetyQA->addWidget(comboBoxSafetyQuestion);
    layoutSafetyQA->addWidget(safetyAnswer);
    layoutSafetyQA->setMargin(defaultMargin);
    gbSafetyQA->setLayout(layoutSafetyQA);
    QObject::connect(comboBoxSafetyQuestion, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updateSafetyAnswerField(const int)));

    textEditMisc = new QTextEdit();

    btnEditEntry = new QPushButton("Save changes", this);
    QObject::connect(btnEditEntry, SIGNAL(clicked()), this, SLOT(saveChanges()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEditWebsite);
    layout->addWidget(gbLogins);
    layout->addWidget(gbCurrentPassword);
    layout->addWidget(gbOldPasswords);
    layout->addWidget(gbSafetyQA);
    layout->addWidget(textEditMisc);
    layout->addWidget(btnEditEntry);
    layout->setMargin(defaultMargin);

    this->setLayout(layout);
}



void
DisplayEntryContent::update(const Account *account)
{
    // Start with cleaning the previous content.

    // Clean 'Logins' fields.
    if (!currentAccount.getLogins().empty())
    {
        // Iterator on the logins list from account.
        QVector<QLineEdit*>::iterator listLoginIt;
        for (listLoginIt = entryLineLogins.begin(); listLoginIt != entryLineLogins.end(); listLoginIt++)
        {
            layoutLogins->removeWidget(*listLoginIt); // Remove QlineEdit from the layout.
            delete *listLoginIt; // Free memory of this login's QLineEdit.
        }
    }
    entryLineLogins.clear();

    // Clean 'oldPwd' field.
    if (!currentAccount.getOldPasswords().empty())
    {
        // Iterator on the password list from account.
        QVector<PasswordEntryLine*>::iterator entryListIt;
        for (entryListIt = entryLineOldPasswords.begin(); entryListIt != entryLineOldPasswords.end(); entryListIt++)
        {
            layoutOldPasswords->removeWidget(*entryListIt); // Remove PasswordEntryLine.
            delete *entryListIt; // Free memory of this PasswordEntryLine.
        }
    }
    entryLineOldPasswords.clear();

    // Clean "safety questions" field.
    comboBoxSafetyQuestion->clear();

    // Clean 'misc' field.
    textEditMisc->clear();

    // Bind the content of this page with the new account infos.
    currentAccount = *account;

    // Fill website field infos.
    lineEditWebsite->setText(QString::fromStdString(currentAccount.getWebsite()));

    // Fill logins list.
    if (!currentAccount.getLogins().empty())
    {
        list<string>::iterator loginsIt;
        list<string> loginsList = currentAccount.getLogins();
        for (loginsIt = loginsList.begin(); loginsIt != loginsList.end(); ++loginsIt)
        {
            entryLineLogins.push_back(new QLineEdit(QString::fromStdString(*loginsIt)));
            layoutLogins->addWidget(entryLineLogins.back());
        }
    }
    try
    {
        entryLineCurrentPassword->setText(
                    cipherEngine.decrypt(QString::fromStdString(currentAccount.getCurrentPassword())));

        // Fill old passwords infos.
        if (!currentAccount.getOldPasswords().empty())
        {
            // Iterator on the password list from account.
            list<string>::iterator oldPwd;
            list<string> tempList = currentAccount.getOldPasswords();
            for (oldPwd = tempList.begin(); oldPwd != tempList.end(); ++oldPwd)
            {
                entryLineOldPasswords.push_back
                        (new PasswordEntryLine(cipherEngine.decrypt(QString::fromStdString(*oldPwd))));
                layoutOldPasswords->addWidget((entryLineOldPasswords.back()));
            }
        }
        //TODO: a call to generate() would probably be better?
    }
    catch (std::runtime_error re)
    {
        // Something went wrong while deciphering a password. The ciphered string doesn't match the password!
        cout << re.what() << endl;
        QMessageBox::warning(this, "Error", "Incorrect password!");
    }
    // Fill safety questions infos.
    if (!currentAccount.getSafetyQuestions().empty())
    {
        comboBoxSafetyQuestion->addItems(currentAccount.getSafetyQuestions());
        updateSafetyAnswerField(0);
    }

    // Fill misc infos.
    if (!currentAccount.getMisc().empty())
    {
        list<string>::iterator miscIt;
        list<string> miscTextList = currentAccount.getMisc();
        for (miscIt = miscTextList.begin(); miscIt != miscTextList.end(); ++miscIt)
        {
            textEditMisc->append(QString::fromStdString(*miscIt));
        }
    }
}



void
DisplayEntryContent::changePassword(void)
{
    ;//TODO
}



void
DisplayEntryContent::saveChanges(void)
{
    ;//TODO
}



void
DisplayEntryContent::updateSafetyAnswerField(const int index)
{
    // As defined in the Qt doc, QComboBox::currentIndexChanged signal can send -1 if the comboBox becomes empty or if
    // index is reset.
    constexpr int resetOrEmptyQComboBoxIndexChangedCode = -1;
    if (index == resetOrEmptyQComboBoxIndexChangedCode)
    {
        safetyAnswer->setText("");
        return;
    }
    try
    {
        safetyAnswer->setText(cipherEngine.decrypt(QString::fromStdString(currentAccount.getSafetyAnswer(index))));
    }
    catch (std::runtime_error re)
    {
        // No need to display a message box asking for the password again.
        cout << re.what() << endl;
    }
}
