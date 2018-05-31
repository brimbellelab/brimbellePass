#include "accountsbook.h"

#include "xmldom.h"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <QString>

using namespace std;

AccountsBook::AccountsBook(void)
{
    // For now, just some dummy content in the combobox.
    Account* amazon = new Account(0, "Amazon", "johndoe@gmail.com", "abcdef");
    amazon->addLogin("johndoe");
    Account* bank = new Account(1, "Bank", "johndoe@gmail.com", "azerty");
    Account* banned = new Account(2, "Banned", "johndoe@gmail.com", "qsdfg");
    Account* irs = new Account(3, "IRS", "johndoe@gmail.com", "wxcvb");
    irs->addOldPassword("tooSimple");
    irs->addOldPassword("StillTooSimple");
    irs->addMisc("I'd like them to forget I exist so that I don't have to pay!");
    irs->addMisc("Last year return: $200");

    this->addAccount(amazon);
    this->addAccount(bank);
    this->addAccount(banned);
    this->addAccount(irs);
}

AccountsBook::AccountsBook(const std::string &xmlFileLogin, const std::string &xmlFilePassword)
{
    // Load logins DOM.
    XmlDom* domLogins = new XmlDom(QString::fromStdString(xmlFileLogin));
    QDomElement loginsRoot = domLogins->getDomDocument()->documentElement();

    // Gonna iterate on children of the root.
    QDomElement loginEntry = loginsRoot.firstChild().toElement();
    while (!loginEntry.isNull())
    {
        // Ensure it's the root of an entry.
        if (loginEntry.tagName() == "entry")
        {
            QString id = loginEntry.attribute("id", "noID");
            QString website = loginEntry.attribute("website", "unknwown");

            // Create a new account for this entry now that we know the id and website.
            Account *account = new Account(id.toUInt(), website.toStdString());

            QDomElement entryChild = loginEntry.firstChild().toElement();
            while (!entryChild.isNull())
            {
                if (entryChild.tagName() == "login")
                {
                    string login = entryChild.firstChild().toText().data().toStdString();
                    account->addLogin(login);
                }
                else if(entryChild.tagName() == "misc")
                {
                    string misc = entryChild.firstChild().toText().data().toStdString();
                    account->addMisc(misc);
                }
                else
                {
                    cout << "tagname not handled yet: " << entryChild.tagName().toStdString() << endl;
                }
                entryChild = entryChild.nextSibling().toElement();
            }
            // Now that the account contains the logins info, it is added to the AccountsBook.
            this->addAccount(account);
        }
        loginEntry = loginEntry.nextSibling().toElement();
    }

    // Load password DOM.
    XmlDom* domPasswords = new XmlDom(QString::fromStdString(xmlFilePassword));
    QDomElement pwdsRoot = domPasswords->getDomDocument()->documentElement();

    // Gonna iterate on children of the root.
    QDomElement pwdEntry = pwdsRoot.firstChild().toElement();
    while (!pwdEntry.isNull())
    {
        // Ensure it's the root of an entry.
        if (pwdEntry.tagName() == "entry")
        {
            QString id = pwdEntry.attribute("id", "noID");
            // Now that we have the ID, the corresponding account can be fetched from the accountsBook.
            Account *account = getAccountPointer(id.toUInt());
            if (account != NULL)
            {
                QDomElement entryChild = pwdEntry.firstChild().toElement();
                while (!entryChild.isNull())
                {
                    if (entryChild.tagName() == "password")
                    {
                        string pwd = entryChild.firstChild().toText().data().toStdString();
                        account->setCurrentPassword(pwd);
                    }
                    else if(entryChild.tagName() == "oldPassword")
                    {
                        string oldPwd = entryChild.firstChild().toText().data().toStdString();
                        account->addOldPassword(oldPwd);
                    }
                    //else if(entryChild.tagName() == "safetyQuestionAnswer") // TODO
                    else
                    {
                        cout << "tagname not handled yet: " << entryChild.tagName().toStdString() << endl;
                    }
                    entryChild = entryChild.nextSibling().toElement();
                }
            }
        }
        pwdEntry = pwdEntry.nextSibling().toElement();
    }
}

void
AccountsBook::addAccount(Account* newAccount)
{
    m_book.insert(newAccount);
}

void
AccountsBook::deleteAccount(uint32_t accountKey)
{

     m_book.erase(m_book.find(getAccountPointer(accountKey)));
}

void
AccountsBook::deleteAccount(const string website)
{
    m_book.erase(m_book.find(getAccountPointer(website)));
}

const Account*
AccountsBook::getAccount(const uint32_t accountKey) const
{
//    return getAccountPointer(accountKey);
    set<Account*>::const_iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((**it).getKey() == accountKey)
        {
            return *it;
        }
    }
    throw string("Account " + to_string(accountKey) + " not found");
}

const Account*
AccountsBook::getAccount(const string website) const
{
    set<Account*>::const_iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((**it).getWebsite() == website)
        {
           return *it;
        }
    }
    throw string("Account "+ website + " not found");
}

QStringList
AccountsBook::getWebsiteList(void)
{
    QStringList websiteList;
    set<Account*>::iterator it;
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        websiteList << QString::fromStdString((**it).getWebsite());
    }
    return websiteList;
}

void
AccountsBook::displayWebsiteList(ostream& stream) const
{
    // TODO return data in alphabetical order.
    set<Account*>::iterator it;
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        stream << (**it).getWebsite();
    }
}

Account*
AccountsBook::getAccountPointer(const uint32_t accountKey)
{
    set<Account*>::iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((**it).getKey() == accountKey)
        {
            return *it;
        }
    }
    throw string("Account " + to_string(accountKey) + " not found");
}

Account*
AccountsBook::getAccountPointer(const string website)
{
    set<Account*>::iterator it;
    // TODO create a functor for that action instead.
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        if ((**it).getWebsite() == website)
        {
            return *it;
        }
    }
    throw string("Account " + website + " not found");
}

ostream& operator<< (ostream& os, const AccountsBook& accountBook)
{
    accountBook.displayWebsiteList(os);
    return os;
}
