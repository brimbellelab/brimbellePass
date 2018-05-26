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
