// MainWindow.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTabWidget>

#include "accountsbook.h"
#include "addentrytab.h"
#include "configfile.h"
#include "configurationtab.h"
#include "displayentrytab.h"
#include "infotab.h"

class MainWindow : public QTabWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    AccountsBook* accountsBook;
    ConfigFile* confFile;
    DisplayEntryTab* displayEntryTab;
    AddEntryTab* addEntryTab;
    ConfigurationTab* configurationTab;
    InfoTab* infoTab;
};

#endif // MAINWINDOW_H
