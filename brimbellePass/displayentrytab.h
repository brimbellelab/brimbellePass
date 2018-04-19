#ifndef DISPLAYENTRYTAB_H
#define DISPLAYENTRYTAB_H

#include <QComboBox>
#include <QWidget>

#include "displayentrycontent.h"

class DisplayEntryTab : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayEntryTab(QWidget *parent = 0);

signals:

public slots:

private:
    QComboBox *comboBoxAccountsList;
    DisplayEntryContent *displayEntryContent;
};

#endif // DISPLAYENTRYTAB_H

