// DisplayEntryContent.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "displayentrycontent.h"

#include "dialognewpassword.h"

#include <algorithm>
#include <iostream>

#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>

using namespace std;

DisplayEntryContent::DisplayEntryContent(QWidget *parent) : QWidget(parent)
{
    bool ok = false;
    cipherEngine.setPassword(QInputDialog::getText(this,
                                                   "Enter password",
                                                   "Enter the main user password",
                                                   QLineEdit::Password,
                                                   QString(),
                                                   &ok));

    gbLogins = new QGroupBox("Logins", this);
    // There should always be an empty login line available.
    entryLineLogins.push_back(new QLineEdit(""));
    QHBoxLayout* layoutLoginsGroupbox = new QHBoxLayout;

    layoutLogins = new QVBoxLayout;
    layoutLogins->addWidget(entryLineLogins[0]);
    layoutLoginsGroupbox->addLayout(layoutLogins);
    QPushButton* btnNewLogin = new QPushButton("+");
    QObject::connect(btnNewLogin, SIGNAL(clicked()), this, SLOT(addLogin()));
    btnNewLogin->setMaximumSize(20 ,20);
    layoutLoginsGroupbox->addWidget(btnNewLogin, 0, Qt::AlignTop);
    gbLogins->setLayout(layoutLoginsGroupbox);

    gbCurrentPassword = new QGroupBox("Current password");
    entryLineCurrentPassword = new PasswordEntryLine("", this);
    btnNewPassword = new QPushButton("+", this);
    btnNewPassword->setMaximumSize(20, 20);
    QObject::connect(btnNewPassword, SIGNAL(clicked()), this, SLOT(changePassword()));
    QHBoxLayout *layoutCurrentPassword = new QHBoxLayout;
    layoutCurrentPassword->addWidget(entryLineCurrentPassword);
    layoutCurrentPassword->addWidget(btnNewPassword);
    layoutCurrentPassword->setMargin(defaultMargin);
    gbCurrentPassword->setLayout(layoutCurrentPassword);

    gbOldPasswords = new QGroupBox("Old passwords");
    layoutOldPasswords = new QVBoxLayout;
    layoutOldPasswords->setMargin(defaultMargin);
    gbOldPasswords->setLayout(layoutOldPasswords);

    safetyQA = new SafetyQAWidget(this, &cipherEngine, defaultMargin);

    textEditMisc = new QTextEdit();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gbLogins);
    layout->addWidget(gbCurrentPassword);
    layout->addWidget(gbOldPasswords);
    layout->addWidget(safetyQA);
    layout->addWidget(textEditMisc);
    layout->setMargin(defaultMargin);

    this->setLayout(layout);
}



void
DisplayEntryContent::clearContent(void)
{
    // Clean 'Logins' fields.
    if (!currentAccount.getLogins().empty())
    {
        // Iterator on the logins list from account.
        QVector<QLineEdit*>::iterator listLoginIt = entryLineLogins.begin();

        // The first login field should not be deleted.
        (*listLoginIt)->setText("");
        ++listLoginIt;
        // The rest should be deleted if present.
        for (; listLoginIt != entryLineLogins.end(); listLoginIt++)
        {
            layoutLogins->removeWidget(*listLoginIt); // Remove QlineEdit from the layout.
            delete *listLoginIt; // Free memory of this login's QLineEdit.
        }
        // Now the array of QLineEdit can be cleared except the first element.
        entryLineLogins.resize(1);
    }

    entryLineCurrentPassword->setText("");

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
    safetyQA->clear();

    // Clean 'misc' field.
    textEditMisc->clear();
}



void
DisplayEntryContent::update(const Account *account)
{
    // Start with cleaning the previous content.
    clearContent();

    // Bind the content of this page with the new account infos.
    currentAccount = *account;

    // Fill logins list.
    if (!currentAccount.getLogins().empty())
    {
        list<string> loginsList = currentAccount.getLogins();
        list<string>::iterator loginsIt = loginsList.begin();
        // The first one is special as the line edit already exists.
        entryLineLogins[0]->setText(QString::fromStdString(*loginsIt));
        ++loginsIt;
        // For the rest new QLineEdit need to be created an appended.
        for (; loginsIt != loginsList.end(); ++loginsIt)
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
        // Another exception is thrown so that the parent can deactivate the save/delete buttons.
        throw QString("Incorrect password!");
    }

    // Fill safety questions infos.
    safetyQA->setData(currentAccount.getSafetyQA());

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
DisplayEntryContent::addLogin(void)
{
    // Check that there is no empty login field already available.
    if (find_if(entryLineLogins.begin(),
                entryLineLogins.end(),
                [&](const QLineEdit* loginField) { return loginField->text().isEmpty();})
        != entryLineLogins.end())
    {
        // There's an empty field available, so no need to create a new field.
        return;
    }
    // No empty field available, so create one.
    entryLineLogins.push_back(new QLineEdit(""));
    layoutLogins->addWidget(entryLineLogins.back());
}



void
DisplayEntryContent::changePassword(void)
{
    DialogNewPassword* dialog = new DialogNewPassword(this);
    if (dialog->exec())
    {
        // Add a new entryLinePassword with the previous password.
        entryLineOldPasswords.append(new PasswordEntryLine(entryLineCurrentPassword->text()));
        layoutOldPasswords->addWidget(entryLineOldPasswords.last());

        // Update the current password with the new one.
        entryLineCurrentPassword->setText(dialog->password());
    }
    delete dialog;
}



void
DisplayEntryContent::saveChanges(Account &accountToSave)
{
    // If a field is empty, it's discarded.

    // Save logins.
    for (auto i = 0; i < entryLineLogins.count(); i++)
    {
        if (!entryLineLogins[i]->text().isEmpty())
        {
            accountToSave.addLogin(entryLineLogins[i]->text().toStdString());
        }
    }

    // Save current password.
    if (!entryLineCurrentPassword->text().isEmpty())
    {
        QString encryptedPassword = cipherEngine.encrypt(entryLineCurrentPassword->text());
        accountToSave.setCurrentPassword(encryptedPassword.toStdString());
    }

    // Save old password.
    for (auto i = 0; i < entryLineOldPasswords.count(); i++)
    {
        if (!entryLineOldPasswords[i]->text().isEmpty())
        {
            QString encryptedOldPassword = cipherEngine.encrypt(entryLineOldPasswords[i]->text());
            accountToSave.addOldPassword(encryptedOldPassword.toStdString());
        }
    }

    // Save Question/Answers.
    for (auto i = 0; i < safetyQA->count(); i++)
    {
        if (!safetyQA->getAnswerCryptedText(i).isEmpty())
        {
            accountToSave.addSafetyQA(safetyQA->getQuestionText(i).toStdString(),
                                      safetyQA->getAnswerCryptedText(i).toStdString());
        }
    }

    // Save Misc.
    if (!textEditMisc->toPlainText().isEmpty())
    {
        accountToSave.addMisc(textEditMisc->toPlainText().toStdString());
    }
}



uint32_t
DisplayEntryContent::getCurrentAccountKey(void)
{
    return currentAccount.getKey();
}
