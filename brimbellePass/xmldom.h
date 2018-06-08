// XmlDom.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef XMLDOM_H
#define XMLDOM_H

#include <QString>
#include <QtXml>
#include <QWidget>

class XmlDom : public QWidget
{
    Q_OBJECT
public:
    explicit XmlDom(const QString &xmlPath, QWidget *parent = 0);
    QDomDocument* getDomDocument(void);
signals:

public slots:

protected:
    QString xmlFilePath;
    QDomDocument *xmlDomDocument;

};

#endif // XMLDOM_H
