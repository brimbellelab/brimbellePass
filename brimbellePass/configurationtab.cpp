// ConfigurationTab.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "configurationtab.h"

#include "dialognewdatabase.h"
#include "xmldom.h"

#include <QMessageBox>
#include <QVBoxLayout>

using namespace std;

ConfigurationTab::ConfigurationTab(ConfigFile *configFile, QWidget *parent) : QWidget(parent)
{
    confFile = configFile;

    // Create config tab widgets
    QVBoxLayout* layout = new QVBoxLayout;
    loginsSource = new XmlInputFileSource("Logins source", confFile->getLoginsFilePath(), this);
    passwordsSource = new XmlInputFileSource("Passwords source", configFile->getPasswordsFilePath(), this);
    btnSaveChanges = new QPushButton("Save");
    connect(btnSaveChanges, SIGNAL(clicked()), this, SLOT(saveChanges()));

    btnCreateNewDatabase = new QPushButton("New database");
    connect(btnCreateNewDatabase, SIGNAL(clicked()), this, SLOT(createNewDatabase()));

    layout->addWidget(loginsSource);
    layout->addWidget(passwordsSource);
    layout->addWidget(btnSaveChanges);
    layout->addWidget(btnCreateNewDatabase);
    layout->addSpacing(300);
    this->setLayout(layout);
}



void
ConfigurationTab::saveChanges(void)
{
    confFile->updateLoginsAndPasswordsFilePath(loginsSource->getPath(), passwordsSource->getPath());

    // TODO: instead of that message, reload the AccountsBook directly.
    QMessageBox::information(this, "Changes saved", "Changes have been saved. Restart BrimbellePass to apply.");
}



void
ConfigurationTab::createNewDatabase(void)
{
    DialogNewDatabase* dialog = new DialogNewDatabase(this);
    if (dialog->exec())
    {
        if (dialog->isDataValid())
        {
            // dialog->newPassword(); // TODO: Nothing done with the new password yet.

            // Update the current password with the new one.
            loginsSource->setPath(dialog->loginsPath());
            passwordsSource->setPath(dialog->passwordsPath());

            //Create a new config file from that.
            saveChanges();
        }
    }
    delete dialog;
}
