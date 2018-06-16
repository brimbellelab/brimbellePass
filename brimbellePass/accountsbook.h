// Accountsbook.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef ACCOUNTSBOOK_H
#define ACCOUNTSBOOK_H

#include <iostream>
#include <set>
#include <string>
#include <utility>

#include <QStringList>

#include "account.h"

class AccountsBook
{
public:
    AccountsBook(void);
    AccountsBook(const std::string &xmlFileLogin, const std::string &xmlFilePassword);
    void addAccount(Account *newAccount);
    void deleteAccount(uint32_t accountKey);
    void deleteAccount(std::string website);
    const Account *getAccount(const uint32_t accountKey) const;
    const Account *getAccount(const std::string website) const;
    QStringList getWebsiteList(void);
    const std::set<uint32_t> getKeysList(void);
    void displayWebsiteList(std::ostream& stream) const;
    uint32_t getAvailableKey(void);
    void saveAccountsBookToXML(void);

private:
    std::set<Account*> m_book;
    Account* getAccountPointer(const uint32_t accountKey);
    Account* getAccountPointer(const std::string website);
};

std::ostream& operator<< (std::ostream& os, const AccountsBook& accountBook);
#endif // ACCOUNTSBOOK_H
