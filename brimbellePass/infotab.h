// Addentrytab.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef INFOTAB_H
#define INFOTAB_H

#include <QPushButton>
#include <QWidget>

class InfoTab : public QWidget
{
    Q_OBJECT
public:
    explicit InfoTab(QWidget *parent = 0);

signals:

public slots:

private slots:
    void openHelp(void);

private:
    QPushButton* btnHelp;
};

#endif // INFOTAB_H
