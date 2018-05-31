#ifndef ACCOUNTSBOOK_H
#define ACCOUNTSBOOK_H

#include <iostream>
#include <set>
#include <string>
#include <utility>

#include <QStringList>

#include "account.h"

/*template <typename T>
struct AccountSortingAlphabetically
{
    bool operator ()(const Account* a, const Account* b) const
    {
       return a->getWebsite(). < b->getWebsite();
    }
};*/

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
    void displayWebsiteList(std::ostream& stream) const;

private:
//    std::set<Account*, AccountSortingAlphabetically<Account*> > m_book;
    std::set<Account*> m_book;
    Account* getAccountPointer(const uint32_t accountKey);
    Account* getAccountPointer(const std::string website);
};

std::ostream& operator<< (std::ostream& os, const AccountsBook& accountBook);
#endif // ACCOUNTSBOOK_H
