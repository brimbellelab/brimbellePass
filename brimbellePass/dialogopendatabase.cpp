// DialogOpenDatabase.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "dialogopendatabase.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QVBoxLayout>

DialogOpenDatabase::DialogOpenDatabase(QWidget *parent) : QDialog(parent)
{
    loginsFilePath = "";
    passwordsFilePath = "";

    loginFileFinder = new XmlInputFileSource("Logins database file", "");
    passwordFileFinder = new XmlInputFileSource("Passwords database file", "");

    btnOk.setText("Ok");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(loginFileFinder);
    layout->addWidget(passwordFileFinder);
    layout->addWidget(&btnOk);

    QObject::connect(&btnOk, SIGNAL(clicked()), this, SLOT(testAndReturn()));

    this->setLayout(layout);
}


bool
DialogOpenDatabase::isDataValid(void)
{
    return dataValid;
}



QString
DialogOpenDatabase::loginsPath(void)
{
    if (!isDataValid())
    {
        throw QString("Invalid data");
    }
    return loginsFilePath;
}



QString
DialogOpenDatabase::passwordsPath(void)
{
    if (!isDataValid())
    {
        throw QString("Invalid data");
    }
    return passwordsFilePath;
}



void
DialogOpenDatabase::testAndReturn(void)
{
    // Check that the passwords file path field is valid.
    if (!(QFileInfo::exists(loginFileFinder->getPath()) && QFileInfo(loginFileFinder->getPath()).isFile()))
    {
        QMessageBox::warning(this, "Passwords file", "The passwords file path is not valid");
        return;
    }
    loginsFilePath = loginFileFinder->getPath();

    // Check that the passwords file path field is valid.
    if (!(QFileInfo::exists(passwordFileFinder->getPath()) && QFileInfo(passwordFileFinder->getPath()).isFile()))
    {
        QMessageBox::warning(this, "Passwords file", "The passwords file path is not valid");
        return;
    }
    passwordsFilePath = passwordFileFinder->getPath();

    dataValid = true;

    this->accept();
}
