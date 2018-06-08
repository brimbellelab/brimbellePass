// XmlDom.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "xmldom.h"

#include <QMessageBox>

#include <iostream>

using namespace std;

XmlDom::XmlDom(const QString &xmlPath, QWidget *parent) : QWidget(parent), xmlFilePath(xmlPath)
{
//    QDomDocument loginXml("loginXml");
    xmlDomDocument = new QDomDocument("xmlDocument");
//    QDomDocument pwdXml("pwdXml");

    QFile xml_doc(xmlFilePath.toStdString().c_str());
    if(!xml_doc.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error while opening the logins file", "The logins file couldn't be opened. Check path in the configuration tab.");
        return;
    }
    if (!xmlDomDocument->setContent(&xml_doc))
    {
        xml_doc.close();
        QMessageBox::warning(this,
                             "Error while opening the XML document",
                             "The XML document couldn't be assigned to the QDomDocument object.");
        return;
    }
    xml_doc.close();

//    QDomElement loginsRoot = xmlDomDocument->documentElement();

//    // Gonna iterate on children of the root.
//    QDomElement loginEntry = loginsRoot.firstChild().toElement();
//    while (!loginEntry.isNull())
//    {
//        // Ensure it's the root of an entry.
//        if (loginEntry.tagName() == "entry")
//        {
//            QString id = loginEntry.attribute("id", "noID");
//            cout << "ID of this entry: " << id.toStdString() << endl;
//            QDomElement entryChild = loginEntry.firstChild().toElement();

//            while (!entryChild.isNull())
//            {
//                if (entryChild.tagName() == "website")
//                {
//                    cout << "tagname website: " << entryChild.firstChild().toText().data().toStdString() << endl;
//                }
//                else if (entryChild.tagName() == "login")
//                {
//                    cout << "tagname login: " << entryChild.firstChild().toText().data().toStdString() << endl;
//                }
//                else
//                {
//                    cout << "tagname not handled yet: " << entryChild.tagName().toStdString() << endl;
//                }
//                entryChild = entryChild.nextSibling().toElement();
//            }
//        }
//        loginEntry = loginEntry.nextSibling().toElement();
//    }
    this->hide();
}


QDomDocument*
XmlDom::getDomDocument(void)
{
    return xmlDomDocument;
}
