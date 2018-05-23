#include "xmldom.h"

#include <QMessageBox>

#include <iostream>

using namespace std;

XmlDom::XmlDom(const char* loginPath, const char* pwdPath, QWidget *parent) : QWidget(parent)
{
    QDomDocument loginXml("loginXml");
//    QDomDocument pwdXml("pwdXml");

    QFile xml_doc(loginPath);//":/xml/loginList.xml");
    if(!xml_doc.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error while opening the logins file", "The logins file couldn't be opened. Check path in the configuration tab.");
        return;
    }
    if (!loginXml.setContent(&xml_doc))
    {
        xml_doc.close();
        QMessageBox::warning(this,
                             "Error while opening the XML document",
                             "The XML document couldn't be assigned to the QDomDocument object.");
        return;
    }

    QDomElement loginsRoot = loginXml.documentElement();

    // Gonna iterate on children of the root.
    QDomElement loginEntry = loginsRoot.firstChild().toElement();
    while (!loginEntry.isNull())
    {
        // Ensure it's the root of an entry.
        if (loginEntry.tagName() == "entry")
        {
            QString id = loginEntry.attribute("id", "noID");
            cout << "ID of this entry: " << id.toStdString() << endl;
            QDomElement entryChild = loginEntry.firstChild().toElement();

            while (!entryChild.isNull())
            {
                if (entryChild.tagName() == "website")
                {
                    cout << "tagname website: " << entryChild.firstChild().toText().data().toStdString() << endl;
                }
                else if (entryChild.tagName() == "login")
                {
                    cout << "tagname login: " << entryChild.firstChild().toText().data().toStdString() << endl;
                }
                else
                {
                    cout << "tagname not handled yet: " << entryChild.tagName().toStdString() << endl;
                }
                entryChild = entryChild.nextSibling().toElement();
            }
        }
        loginEntry = loginEntry.nextSibling().toElement();
    }
}
