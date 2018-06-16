// ConfigFile.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "configfile.h"

#include <iostream>
#include <QMessageBox>

using namespace std;

ConfigFile::ConfigFile(QWidget *parent) : QWidget(parent)
{
    // Load configuration file.
    confFilePath = QCoreApplication::applicationDirPath();
    confFilePath.append("/");
    confFilePath.append(confFileName);

    QFile confFile(confFilePath);
    if (!confFile.exists())
    {
        // First time BrimbellePass is started?
        QMessageBox::warning(this, "No configuration file found", "A new empty configuration file will be created.");
        createConfFile();
    }
    if(!confFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error", "Can't open configuration file");
    }
    if (!brimbelleConf.setContent(&confFile))
    {
        // File exists but content is incorrect.
        QMessageBox::warning(this, "No configuration file found", "Can't get config from configuration file");
    }
    confFile.close();
    getXmlLoginAndPwdPathFromConfigFile();
}



QString
ConfigFile::getLoginsFilePath(void)
{
    return xmlLoginPath;
}



QString
ConfigFile::getPasswordsFilePath(void)
{
    return xmlPwdPath;
}



bool
ConfigFile::updateLoginsAndPasswordsFilePath(const QString &loginsFilePath, const QString &passwordsFilePath)
{
    // TODO Test if the logins and passwords files exist.

    QFile confFile(confFilePath);
    if (confFile.open(QIODevice::WriteOnly))
    {
        QDomElement configRoot = brimbelleConf.documentElement();
        // Gonna iterate on children of the root.
        QDomElement configElement = configRoot.firstChild().toElement();
        while (!configElement.isNull())
        {
            if (configElement.tagName() == "loginFilePath")
            {
                configElement.firstChild().setNodeValue(loginsFilePath);
            }
            else if (configElement.tagName() == "passwordFilePath")
            {
                configElement.firstChild().setNodeValue(passwordsFilePath);
            }
            else
            {
                cout << "tagname not handled yet: " << configElement.tagName().toStdString() << endl;
            }
            configElement = configElement.nextSibling().toElement();
        }

        QString domString = brimbelleConf.toString();

        QTextStream writeConfFileStream(&confFile);
        writeConfFileStream << domString;

        // Now that it has been succesfully saved, update the private variables.
        xmlLoginPath = loginsFilePath;
        xmlPwdPath = passwordsFilePath;
    }
    else
    {
        QMessageBox::critical(this, "Save configuration file", "The configuration file couldn't be saved");
        return false;
    }
    confFile.close();

    return true;
}



void
ConfigFile::createConfFile(void)
{
    QFile confFile(confFilePath);

    if (confFile.open(QIODevice::WriteOnly))
    {
        // Generate XML structure;
        QDomDocument emptyDoc("BrimbellePassConfigFile");

        // Root element.
        QDomElement brimbellePassConfElement = emptyDoc.createElement("brimbellePassConf");
        emptyDoc.appendChild(brimbellePassConfElement);

        // Logins file path element.
        QDomElement loginFilePathElement = emptyDoc.createElement("loginFilePath");
        brimbellePassConfElement.appendChild(loginFilePathElement);
        QDomText loginFilePathValue = emptyDoc.createTextNode("logins.xml");
        loginFilePathElement.appendChild(loginFilePathValue);

        // Passwords file path element.
        QDomElement passwordFilePathElement = emptyDoc.createElement("passwordFilePath");
        brimbellePassConfElement.appendChild(passwordFilePathElement);
        QDomText passwordFilePathValue = emptyDoc.createTextNode("passwords.xml");
        passwordFilePathElement.appendChild(passwordFilePathValue);

        // Writing the DOM into the config file.
        QString domString = emptyDoc.toString();
        QTextStream writeConfFileStream(&confFile);
        writeConfFileStream << domString;
    }
    else
    {
        QMessageBox::warning(this, "Create configuration file", "The configuration file couldn't be created");
    }
    confFile.close();
}



void
ConfigFile::getXmlLoginAndPwdPathFromConfigFile(void)
{
    QDomElement configRoot = brimbelleConf.documentElement();

    // Gonna iterate on children of the root.
    QDomElement configElement = configRoot.firstChild().toElement();
    while (!configElement.isNull())
    {
        if (configElement.tagName() == "loginFilePath")
        {
            xmlLoginPath = configElement.firstChild().toText().data();
            cout << "loginFilePath: " << xmlLoginPath.toStdString() << endl;
        }
        else if (configElement.tagName() == "passwordFilePath")
        {
            xmlPwdPath = configElement.firstChild().toText().data();
            cout << "passwordFilePath: " << xmlPwdPath.toStdString() << endl;
        }
        else
        {
            cout << "tagname not handled yet: " << configElement.tagName().toStdString() << endl;
        }
        configElement = configElement.nextSibling().toElement();
    }
}
