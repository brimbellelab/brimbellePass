#include "displayentrycontent.h"

#include <algorithm>

#include <QVBoxLayout>

using namespace std;

DisplayEntryContent::DisplayEntryContent(QWidget *parent) : QWidget(parent)
{
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
    gbCurrentPassword->setLayout(layoutCurrentPassword);

    gbOldPasswords = new QGroupBox("Old passwords");
    layoutOldPasswords = new QVBoxLayout;
    gbOldPasswords->setLayout(layoutOldPasswords);

    textEditMisc = new QTextEdit();

    btnEditEntry = new QPushButton("Save changes", this);
    QObject::connect(btnEditEntry, SIGNAL(clicked()), this, SLOT(saveChanges()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEditWebsite);
    layout->addWidget(gbLogins);
    layout->addWidget(gbCurrentPassword);
    layout->addWidget(gbOldPasswords);
    layout->addWidget(textEditMisc);
    layout->addWidget(btnEditEntry);

    this->setLayout(layout);
}



void DisplayEntryContent::update(const Account &account)
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

    // Clean 'misc' field.
    textEditMisc->clear();

    // Bind the content of this page with the new account infos.
    currentAccount = account;

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
    entryLineCurrentPassword->setText(QString::fromStdString(currentAccount.getCurrentPassword()));

    // Fill old passwords infos.
    if (!currentAccount.getOldPasswords().empty())
    {
        // Iterator on the password list from account.
        list<string>::iterator oldPwd;
        list<string> tempList = currentAccount.getOldPasswords();
        for (oldPwd = tempList.begin(); oldPwd != tempList.end(); ++oldPwd)
        {
            entryLineOldPasswords.push_back(new PasswordEntryLine(QString::fromStdString(*oldPwd)));
            layoutOldPasswords->addWidget((entryLineOldPasswords.back()));
        }
    }
    //TODO: a call to generate() would probably be better?

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

