#include "configurationtab.h"

#include "xmldom.h"

#include <QVBoxLayout>

#include <iostream>

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

    layout->addWidget(loginsSource);
    layout->addWidget(passwordsSource);
    layout->addWidget(btnSaveChanges);
    layout->addSpacing(300);
    this->setLayout(layout);
}



void
ConfigurationTab::saveChanges(void)
{
    confFile->updateLoginsAndPasswordsFilePath(loginsSource->getPath(), passwordsSource->getPath());
}

