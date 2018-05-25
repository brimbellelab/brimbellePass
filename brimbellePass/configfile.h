#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QtXml>
#include <QWidget>

class ConfigFile : public QWidget
{
    Q_OBJECT
public:
    ConfigFile(QWidget *parent = 0);
    QString getLoginsFilePath(void);
    QString getPasswordsFilePath(void);
    bool updateLoginsAndPasswordsFilePath(const QString &loginsFilePath, const QString &passwordsFilePath);

public slots:

private:
    static constexpr auto confFileName = "brimbellepass.conf";
    QString confFilePath;
    QDomDocument brimbelleConf;
    QString xmlLoginPath;
    QString xmlPwdPath;

    void getXmlLoginAndPwdPathFromConfigFile(void);
    void createConfFile(void);
};

#endif // CONFIGFILE_H
