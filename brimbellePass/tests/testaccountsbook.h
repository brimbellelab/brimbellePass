// testaccountsbook.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#pragma once

#include <QtTest/QtTest>

#include "../accountsbook.h"

class TestAccountsBook: public QObject
{
    Q_OBJECT

private slots:
    void deleteAccount(void);
    void addAccount(void);
    void getAvailableKey(void);

private:
    AccountsBook accountsBook;
};
