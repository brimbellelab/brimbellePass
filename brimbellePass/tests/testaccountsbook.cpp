// testaccountsbook.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include <QtTest/QtTest>

#include "testaccountsbook.h"

void
TestAccountsBook::deleteAccount(void)
{
    if (accountsBook.getWebsiteList().isEmpty())
    {
        QSKIP("There must be at least one account in the accountsBook to test deleteAccount()");
        return;
    }

    auto numberOfAccounts = accountsBook.getWebsiteList().count();
    QString firstAccountName = accountsBook.getWebsiteList().first();
    accountsBook.deleteAccount(firstAccountName.toStdString());
    QCOMPARE(accountsBook.getWebsiteList().count(), numberOfAccounts - 1);
}



void
TestAccountsBook::addAccount(void)
{
    std::string accountName = "Account #1";
    auto numberOfAccounts = accountsBook.getWebsiteList().count();
    accountsBook.addAccount(new Account(1, accountName));
    QCOMPARE(accountsBook.getWebsiteList().count(), numberOfAccounts + 1);
}
