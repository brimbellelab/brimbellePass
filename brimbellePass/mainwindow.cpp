#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow() : QTabWidget()
{
    confFile = new ConfigFile();
    accountsBook = new AccountsBook(confFile->getLoginsFilePath().toStdString(),
                                    confFile->getPasswordsFilePath().toStdString());

    setFixedSize(400, 650);

    // Create the 3 tabs of the main window.
    displayEntryTab = new DisplayEntryTab(accountsBook, this);
    addEntryTab = new AddEntryTab();
    configurationTab = new ConfigurationTab(confFile);
    this->addTab(displayEntryTab, "Main");
    this->addTab(addEntryTab, "Add");
    this->addTab(configurationTab, "Parameters");
}



MainWindow::~MainWindow()
{
    delete displayEntryTab;
    delete configurationTab;
    delete addEntryTab;
    delete accountsBook;
}
