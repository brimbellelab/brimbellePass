#include "displayentrytab.h"

#include "account.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QString>

DisplayEntryTab::DisplayEntryTab(QWidget *parent) : QWidget(parent)
{
    comboBoxAccountsList = new QComboBox(this);

    // @todo: Replace with dynamic read of an XML file whenever possible.
    // For now, just some dummy content in the combobox.
    Account amazon = Account(0, "Amazon", "johndoe@gmail.com", "abcdef");
    amazon.addLogin("johndoe");
    Account bank = Account(1, "Bank", "johndoe@gmail.com", "azerty");
    Account banned = Account(2, "Banned", "johndoe@gmail.com", "qsdfg");
    Account irs = Account(3, "IRS", "johndoe@gmail.com", "wxcvb");
    irs.addOldPassword("tooSimple");
    irs.addOldPassword("StillTooSimple");
    irs.addMisc("I'd like them to forget I exist so that I don't have to pay!");
    irs.addMisc("Last year return: $200");

    accountsBook = new AccountsBook();
    accountsBook->addAccount(amazon);
    accountsBook->addAccount(bank);
    accountsBook->addAccount(banned);
    accountsBook->addAccount(irs);

    comboBoxAccountsList->addItems(accountsBook->getWebsiteList());

    QObject::connect(comboBoxAccountsList, SIGNAL(currentIndexChanged(const QString&)),
                     this, SLOT(reloadEntryContent(const QString&)));

    displayEntryContent = new DisplayEntryContent(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(comboBoxAccountsList);
    verticalLayout->addWidget(displayEntryContent);

    this->setLayout(verticalLayout);

    if (comboBoxAccountsList->count() > 0)
    {
        reloadEntryContent(comboBoxAccountsList->itemText(0));
    }
}



void
DisplayEntryTab::reloadEntryContent(const QString& text)
{
    displayEntryContent->update(accountsBook->getAccount(text.toStdString()));
}
