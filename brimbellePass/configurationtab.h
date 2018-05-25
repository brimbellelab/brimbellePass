#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include "configfile.h"
#include "xmlinputfilesource.h"

#include <QPushButton>
#include <QWidget>

class ConfigurationTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationTab(ConfigFile *configFile, QWidget *parent = 0);
signals:

public slots:

private slots:
    void saveChanges(void);

private:
    ConfigFile *confFile;
    QPushButton *btnSaveChanges;
    XmlInputFileSource *loginsSource;
    XmlInputFileSource *passwordsSource;
};

#endif // CONFIGURATIONTAB_H
