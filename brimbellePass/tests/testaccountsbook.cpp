// testaccountsbook.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include <QtTest/QtTest>

#include "testaccountsbook.h"

#include "../account.h"

void
TestAccountsBook::deleteAccount(void)
{
    std::string account1Name = "Account #1";
    accountsBook.addAccount(new Account(1, account1Name));
    std::string account2Name = "Account #2";
    accountsBook.addAccount(new Account(2, account2Name));

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



void
TestAccountsBook::getAvailableKey(void)
{
    // Create an empty accountsBook.
    AccountsBook* accountsBookAvailableKey = new AccountsBook();

    // Adding this test as getAvailableKey use to crash on an empty accountsBook.
    QCOMPARE(accountsBookAvailableKey->getAvailableKey(), 1u);

    accountsBookAvailableKey->addAccount(new Account(2u));// Create an account with a key of 2.
    accountsBookAvailableKey->addAccount(new Account(4u));// Create an account with a key of 4.
    accountsBookAvailableKey->addAccount(new Account(5u));// Create an account with a key of 5.

    // With these data the first available key should be 1.
    QCOMPARE(accountsBookAvailableKey->getAvailableKey(), 1u);
    accountsBookAvailableKey->addAccount(new Account(1u));// Create an account with a key of 1.

    QCOMPARE(accountsBookAvailableKey->getAvailableKey(), 3u);
    accountsBookAvailableKey->addAccount(new Account(3u));// Create an account with a key of 3.

    QCOMPARE(accountsBookAvailableKey->getAvailableKey(), 6u);
    delete accountsBookAvailableKey;
}



void
TestAccountsBook::exists(void)
{
    AccountsBook* accountsBookExists = new AccountsBook();

    QVERIFY(!accountsBookExists->exists("Account1"));

    accountsBookExists->addAccount(new Account(1, "Account1"));// Create an account with a key of 1, and a name "Account1".
    QVERIFY(accountsBookExists->exists("Account1"));

    accountsBookExists->addAccount(new Account(2, "Account2"));// Create an account with a key of 1, and a name "Account2".
    QVERIFY(accountsBookExists->exists("Account1"));

    QVERIFY(!accountsBookExists->exists("Account3"));

    delete accountsBookExists;
}
