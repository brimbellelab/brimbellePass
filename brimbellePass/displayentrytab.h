#ifndef DISPLAYENTRYTAB_H
#define DISPLAYENTRYTAB_H

#include <QComboBox>
#include <QString>
#include <QWidget>

#include "accountsbook.h"
#include "displayentrycontent.h"

class DisplayEntryTab : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayEntryTab(QWidget *parent = 0);

signals:

public slots:
    void reloadEntryContent(const QString& text);

private:
    QComboBox *comboBoxAccountsList;
    DisplayEntryContent *displayEntryContent;
    ///@note this can only be temporary as it should be possible to modify it from the other tabs...
    AccountsBook *accountsBook;
};

#endif // DISPLAYENTRYTAB_H

