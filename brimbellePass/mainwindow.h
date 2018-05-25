#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTabWidget>

#include "accountsbook.h"
#include "addentrytab.h"
#include "configfile.h"
#include "configurationtab.h"
#include "displayentrytab.h"

class MainWindow : public QTabWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    AccountsBook *accountsBook;
    ConfigFile *confFile;
    DisplayEntryTab *displayEntryTab;
    AddEntryTab *addEntryTab;
    ConfigurationTab *configurationTab;
};

#endif // MAINWINDOW_H
