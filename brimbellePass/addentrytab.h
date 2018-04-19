#ifndef ADDENTRYTAB_H
#define ADDENTRYTAB_H

#include <QLabel>
#include <QWidget>

class AddEntryTab : public QWidget
{
    Q_OBJECT
public:
    explicit AddEntryTab(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *label;
};

#endif // ADDENTRYTAB_H
