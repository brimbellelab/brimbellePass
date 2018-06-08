// Addentrytab.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

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
