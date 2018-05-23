#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include "xmlinputfilesource.h"

#include <QLabel>
#include <QtXml>
#include <QWidget>

class ConfigurationTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationTab(QWidget *parent = 0);

signals:

public slots:

private:
    static constexpr auto confFilePath = ":/conf/brimbellepass.conf";
    QLabel *label;
    QDomDocument brimbelleConf;
    QString xmlLoginPath;
    QString xmlPwdPath;
    XmlInputFileSource *loginsSource;
    XmlInputFileSource *passwordsSource;

    void getXmlLoginAndPwdPath(void);
    void createConfFile(void);

};

#endif // CONFIGURATIONTAB_H
