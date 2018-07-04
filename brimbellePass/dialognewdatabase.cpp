// DialogNewDatabase.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "dialognewdatabase.h"

#include <QFile>
#include <QMessageBox>
#include <QObject>

DialogNewDatabase::DialogNewDatabase(QWidget *parent) : QDialog(parent)
{
    newPwd = "";
    loginsFilePath = "";
    passwordsFilePath = "";

    labelLoginsFile.setText("Logins database file");
    labelPasswordsFile.setText("Passwords database file");

    btnOk.setText("Ok");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&labelLoginsFile);
    layout->addWidget(&loginFileFinder);
    layout->addWidget(&labelPasswordsFile);
    layout->addWidget(&passwordFileFinder);
    layout->addWidget(&newPasswordWidget);
    layout->addWidget(&btnOk);

    QObject::connect(&btnOk, SIGNAL(clicked()), this, SLOT(testAndReturn()));

    this->setLayout(layout);
}



bool
DialogNewDatabase::isDataValid(void)
{
    return dataValid;
}



QString
DialogNewDatabase::loginsPath(void)
{
    if (!isDataValid())
    {
        throw QString("Invalid data");
    }
    return loginsFilePath;
}



QString
DialogNewDatabase::passwordsPath(void)
{
    if (!isDataValid())
    {
        throw QString("Invalid data");
    }
    return passwordsFilePath;
}



QString
DialogNewDatabase::newPassword(void)
{
    if (!isDataValid())
    {
        throw QString("Invalid data");
    }
    return newPwd;
}



void
DialogNewDatabase::testAndReturn(void)
{
    // Start by checking that the new password is valid.
    try
    {
        newPwd = newPasswordWidget.data();
    }
    catch (NewPasswordWidgetStatus status)
    {
        // When the password is not valid an expection is thrown.
        newPasswordWidget.displayMessageBoxStatus(status);
        return;
    }

    // Check that the logins file path field is not empty.
    // Try to create a new logins database from the resource file.
    if (!QFile::copy(":emptyXmlFiles/emptyLoginsDatabase.xml", loginFileFinder.text()))
    {
        QMessageBox::warning(this, "Logins file", "The logins file path is not valid");
        return;
    }
    if (!QFile::setPermissions(loginFileFinder.text(), QFileDevice::ReadOwner | QFileDevice::WriteOwner))
    {
        QMessageBox::warning(this, "Logins file", "The logins file permission couldn't be set");
        return;
    }
    loginsFilePath = loginFileFinder.text();

    // Check that the passwords file path field is not empty.
    // Try to create a new passwords database from the resource file.
    if (!QFile::copy(":emptyXmlFiles/emptyPasswordsDatabase.xml", passwordFileFinder.text()))
    {
        QMessageBox::warning(this, "Passwords file", "The passwords file path is not valid");
        return;
    }
    if (!QFile::setPermissions(passwordFileFinder.text(), QFileDevice::ReadOwner | QFileDevice::WriteOwner))
    {
        QMessageBox::warning(this, "Logins file", "The passwords file permission couldn't be set");
        return;
    }
    passwordsFilePath = passwordFileFinder.text();

    dataValid = true;

    this->accept();
}
