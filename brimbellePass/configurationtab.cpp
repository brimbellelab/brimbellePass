#include "configurationtab.h"

#include "xmldom.h"

ConfigurationTab::ConfigurationTab(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("Configuration", this);
    XmlDom *dom = new XmlDom();
    dom->hide();
}
