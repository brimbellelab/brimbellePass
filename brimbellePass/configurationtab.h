#ifndef CONFIGURATIONTAB_H
#define CONFIGURATIONTAB_H

#include <QLabel>
#include <QWidget>

class ConfigurationTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationTab(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *label;
};

#endif // CONFIGURATIONTAB_H
