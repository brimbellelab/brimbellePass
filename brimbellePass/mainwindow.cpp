// MainWindow.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow() : QTabWidget()
{
    try
    {
        confFile = new ConfigFile(this);
    }
    catch (QString e)
    {
        qApp->exit();
        return;
    }

    accountsBook = new AccountsBook(confFile->getLoginsFilePath().toStdString(),
                                    confFile->getPasswordsFilePath().toStdString());

    setFixedSize(400, 650);

    // Create the 3 tabs of the main window.
    displayEntryTab = new DisplayEntryTab(accountsBook, this);
    configurationTab = new ConfigurationTab(confFile);
    infoTab = new InfoTab();
    this->addTab(displayEntryTab, "Main");
    this->addTab(configurationTab, "Parameters");
    this->addTab(infoTab, "Info");
}



MainWindow::~MainWindow()
{
    delete accountsBook;
}
