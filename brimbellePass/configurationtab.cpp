#include "configurationtab.h"

#include "xmldom.h"

#include <QVBoxLayout>
#include <QMessageBox>

#include <iostream>

using namespace std;

ConfigurationTab::ConfigurationTab(QWidget *parent) : QWidget(parent)
{
    // Load configuration file.
    confFilePath = QCoreApplication::applicationDirPath();
    confFilePath.append("/");
    confFilePath.append(confFileName);

    QFile confFile(confFilePath);
    if (!confFile.exists())
    {
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
    getXmlLoginAndPwdPath();

    // Load logins and passwords DOM.
    XmlDom *dom = new XmlDom(xmlLoginPath.toStdString().c_str(),
                             xmlPwdPath.toStdString().c_str());
    dom->hide();

    // Create config tab widgets
    QVBoxLayout* layout = new QVBoxLayout;
    loginsSource = new XmlInputFileSource("Logins source", xmlLoginPath, this);
    passwordsSource = new XmlInputFileSource("Passwords source", xmlPwdPath, this);
    btnSaveChanges = new QPushButton("Save");

    connect(loginsSource, SIGNAL(pathChanged(QString)), this, SLOT(updateXmlLoginsPath(QString)));
    connect(passwordsSource, SIGNAL(pathChanged(QString)), this, SLOT(updateXmlPasswordsPath(QString)));

    connect(btnSaveChanges, SIGNAL(clicked()), this, SLOT(updateConfFile()));

    layout->addWidget(loginsSource);
    layout->addWidget(passwordsSource);
    layout->addWidget(btnSaveChanges);
    layout->addSpacing(300);
    this->setLayout(layout);
}

void
ConfigurationTab::getXmlLoginAndPwdPath(void)
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



void
ConfigurationTab::createConfFile(void)
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

        // Passwords fifle path element.
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
ConfigurationTab::updateConfFile(void)
{
    QDomElement configRoot = brimbelleConf.documentElement();

    // Gonna iterate on children of the root.
    QDomElement configElement = configRoot.firstChild().toElement();
    while (!configElement.isNull())
    {
        if (configElement.tagName() == "loginFilePath")
        {
            configElement.firstChild().setNodeValue(xmlLoginPath);
        }
        else if (configElement.tagName() == "passwordFilePath")
        {
            configElement.firstChild().setNodeValue(xmlPwdPath);
        }
        else
        {
            cout << "tagname not handled yet: " << configElement.tagName().toStdString() << endl;
        }
        configElement = configElement.nextSibling().toElement();
    }

    QString domString = brimbelleConf.toString();
    QFile confFile(confFilePath);
    if (confFile.open(QIODevice::WriteOnly))
    {
        QTextStream writeConfFileStream(&confFile);
        writeConfFileStream << domString;
    }
    else
    {
        QMessageBox::critical(this, "Save configuration file", "The configuration file couldn't be saved");
    }
    confFile.close();
}



void
ConfigurationTab::updateXmlLoginsPath(QString path)
{
    xmlLoginPath = path;
}



void
ConfigurationTab::updateXmlPasswordsPath(QString path)
{
    xmlPwdPath = path;
}
