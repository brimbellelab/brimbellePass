#ifndef XMLDOM_H
#define XMLDOM_H

#include <QWidget>
#include <QtXml>

class XmlDom : public QWidget
{
    Q_OBJECT
public:
    explicit XmlDom(const char* loginPath, const char* pwdPath, QWidget *parent = 0);

signals:

public slots:

};

#endif // XMLDOM_H
