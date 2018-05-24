#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include "xmlinputfilesource.h"

#include <QPushButton>
#include <QtXml>
#include <QWidget>

class ConfigurationTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationTab(QWidget *parent = 0);

signals:

public slots:

private slots:
    void updateConfFile(void);
    void updateXmlLoginsPath(QString path);
    void updateXmlPasswordsPath(QString path);

private:
    static constexpr auto confFileName = "brimbellepass.conf";
    QString confFilePath;
    QPushButton *btnSaveChanges;
    QDomDocument brimbelleConf;
    QString xmlLoginPath;
    QString xmlPwdPath;
    XmlInputFileSource *loginsSource;
    XmlInputFileSource *passwordsSource;

    void getXmlLoginAndPwdPath(void);
    void createConfFile(void);
};

#endif // CONFIGURATIONTAB_H
