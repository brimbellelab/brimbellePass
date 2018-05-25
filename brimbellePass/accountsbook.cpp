#include "accountsbook.h"

#include "xmldom.h"

#include <iostream>
#include <iterator>

#include <QString>

using namespace std;

AccountsBook::AccountsBook(void)
{
    // @todo: Replace with dynamic read of an XML file whenever possible.
    // For now, just some dummy content in the combobox.
    Account amazon = Account(0, "Amazon", "johndoe@gmail.com", "abcdef");
    amazon.addLogin("johndoe");
    Account bank = Account(1, "Bank", "johndoe@gmail.com", "azerty");
    Account banned = Account(2, "Banned", "johndoe@gmail.com", "qsdfg");
    Account irs = Account(3, "IRS", "johndoe@gmail.com", "wxcvb");
    irs.addOldPassword("tooSimple");
    irs.addOldPassword("StillTooSimple");
    irs.addMisc("I'd like them to forget I exist so that I don't have to pay!");
    irs.addMisc("Last year return: $200");

    this->addAccount(amazon);
    this->addAccount(bank);
    this->addAccount(banned);
    this->addAccount(irs);
}

AccountsBook::AccountsBook(const std::string &xmlFileLogin, const std::string &xmlFilePassword)
{
    cout << "Path to logins file: " << xmlFileLogin << endl;
    cout << "Path to passwords file: " << xmlFilePassword << endl;

    // Load logins and passwords DOM.
    XmlDom* domAccounts = new XmlDom(xmlFileLogin.c_str(),
                             xmlFilePassword.c_str());

//    fillAccountsBookFromDom;
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
