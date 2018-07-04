// ConfigurationTab.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include "configfile.h"
#include "xmlinputfilesource.h"

#include <QPushButton>
#include <QWidget>

class ConfigurationTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationTab(ConfigFile *configFile, QWidget *parent = 0);
signals:

public slots:

private slots:
    void saveChanges(void);
    void createNewDatabase(void);

private:
    ConfigFile* confFile;
    QPushButton* btnSaveChanges;
    QPushButton* btnCreateNewDatabase;
    XmlInputFileSource* loginsSource;
    XmlInputFileSource* passwordsSource;
};

#endif // CONFIGURATIONTAB_H
