#include "configurationtab.h"

#include "xmldom.h"

#include <QVBoxLayout>
#include <QMessageBox>

#include <iostream>

using namespace std;

ConfigurationTab::ConfigurationTab(QWidget *parent) : QWidget(parent)
{
    // Load configuration file.
    QFile confFile(confFilePath);
    if (!confFile.exists())
    {
        QMessageBox::warning(this, "No configuration file found", "A new empty configuration file will be created.");
        createConfFile();
    }
    if (!brimbelleConf.setContent(&confFile))
    {
        QMessageBox::warning(this, "No configuration file found", "Can't get config from configuration file");
    }
    getXmlLoginAndPwdPath();

    // Load logins and passwords DOM.
    XmlDom *dom = new XmlDom(xmlLoginPath.toStdString().c_str(),
                             xmlPwdPath.toStdString().c_str());
    dom->hide();

    // Create config tab widgets
    QVBoxLayout* layout = new QVBoxLayout;
    loginsSource = new XmlInputFileSource("Logins source", xmlLoginPath, this);
    passwordsSource = new XmlInputFileSource("Passwords source", xmlPwdPath, this);

    layout->addWidget(loginsSource);
    layout->addWidget(passwordsSource);
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
        // TODO generate XML structure;
        ;
    }
    else
    {
        QMessageBox::warning(this, "Create configuration file", "The configuration file couldn't be created");
    }
}
