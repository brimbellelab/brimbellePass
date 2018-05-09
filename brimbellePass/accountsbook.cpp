#include "accountsbook.h"

#include <iterator>
#include <QString>

using namespace std;

AccountsBook::AccountsBook(void)
{
    ;
}

void
AccountsBook::addAccount(Account& newAccount)
{
    m_book.insert(newAccount);
}

void
AccountsBook::deleteAccount(uint32_t accountKey)
{

     m_book.erase(m_book.find(getAccount(accountKey)));
}

void
AccountsBook::deleteAccount(const string website)
{
    m_book.erase(m_book.find(getAccount(website)));
}

Account
AccountsBook::getAccount(const uint32_t accountKey)
{
    set<Account>::iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((*it).getKey() == accountKey)
        {
            return *it;
        }
    }
    throw string("Account " + to_string(accountKey) + " not found");
}

Account
AccountsBook::getAccount(const string website)
{
    set<Account>::iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((*it).getWebsite() == website)
        {
            return *it;
        }
    }
    throw string("Account "+ website + " not found");
}

QStringList
AccountsBook::getWebsiteList(void)
{
    QStringList websiteList;//m_book.size());
    set<Account>::iterator it;
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        websiteList << QString::fromStdString((*it).getWebsite());
    }
    return websiteList;
}

void
AccountsBook::displayWebsiteList(ostream& stream) const
{
    set<Account>::iterator it;
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        stream << (*it).getWebsite();
    }
}

ostream& operator<< (ostream& os, const AccountsBook& accountBook)
{
    accountBook.displayWebsiteList(os);
    return os;
}
