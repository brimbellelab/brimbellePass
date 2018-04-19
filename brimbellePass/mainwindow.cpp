#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow() : QTabWidget()
{
    setFixedSize(400, 600);

    // Create the 3 tabs of the main window.
    displayEntryTab = new DisplayEntryTab();
    addEntryTab = new AddEntryTab();
    configurationTab = new ConfigurationTab();
    this->addTab(displayEntryTab, "Main");
    this->addTab(addEntryTab, "Add");
    this->addTab(configurationTab, "Parameters");
}



MainWindow::~MainWindow()
{
    delete displayEntryTab;
    delete configurationTab;
    delete addEntryTab;
}
