#include "displayentrytab.h"

#include "account.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QString>

DisplayEntryTab::DisplayEntryTab(AccountsBook *accounts, QWidget *parent) : QWidget(parent)
{
    accountsBook = accounts;
    comboBoxAccountsList = new QComboBox(this);

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
