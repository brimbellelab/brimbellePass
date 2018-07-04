// ConfigFile.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

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
    void createConfFile(void);
public slots:

private:
    static constexpr auto confFileName = "brimbellepass.conf";
    QString confFilePath;
    QDomDocument brimbelleConf;
    QString xmlLoginPath;
    QString xmlPwdPath;

    void getXmlLoginAndPwdPathFromConfigFile(void);
};

#endif // CONFIGFILE_H
