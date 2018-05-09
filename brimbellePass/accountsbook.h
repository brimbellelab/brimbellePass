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
// TODO    AccountBook(xmlFileLogin, xmlFilePassword);
    void addAccount(Account& newAccount);
    void deleteAccount(uint32_t accountKey);
    void deleteAccount(std::string website);
    Account getAccount(const uint32_t accountKey);
    Account getAccount(const std::string website);
    QStringList getWebsiteList(void);
    void displayWebsiteList(std::ostream& stream) const;

private:
    std::set<Account> m_book;
};

std::ostream& operator<< (std::ostream& os, const AccountsBook& accountBook);
#endif // ACCOUNTSBOOK_H
