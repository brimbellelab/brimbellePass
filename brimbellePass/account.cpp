// Account.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "account.h"

#include <iostream>

using namespace std;

class sortAccountsByKey
{
public:
    bool operator()(const Account &a, const Account& b)
    {
        return a.getKey() < b.getKey();
    }
};



class sortAccountByWebsite
{
    bool operator()(const Account &a, const Account& b)
    {
        return a.getWebsite() < b.getWebsite();
    }
};



Account::Account(void)
{
    m_key = 0;
    m_website = "Empty account";
}



Account::Account(uint32_t key)
{
    m_key = key;
    m_website = "Empty account";
}



Account::Account(uint32_t key, string website)
{
    m_key = key;
    m_website = website;
}



Account::Account(uint32_t key,
        string website,
        string login,
        string currentPassword)
{
    m_key = key;
    m_website = website;
    m_logins.push_back(login);
    m_currentPassword = currentPassword;
}



Account::Account(uint32_t key,
        string website,
        list<string> logins,
        string currentPassword,
        list<string> oldPasswords,
        std::vector<std::pair<string, string> > safetyQA,
        list<string> misc)
{
    m_key = key;
    m_website = website;
    m_logins = logins;
    m_currentPassword = currentPassword;
    m_oldPasswords = oldPasswords;
    m_safetyQA = safetyQA;
    m_misc = misc;
}



void
Account::addLogin(string newLogin)
{
    m_logins.push_back(newLogin);
}



void
Account::setCurrentPassword(string password)
{
    m_currentPassword = password;
}



void
Account::addOldPassword(string oldPassword)
{
    m_oldPasswords.push_front(oldPassword);
}



void
Account::changeCurrentPassword(string newPassword)
{
    Account::addOldPassword(m_currentPassword);
    Account::setCurrentPassword(newPassword);
}



void
Account::addSafetyQA(string question, string answer)
{
    m_safetyQA.push_back(pair<string, string>(question, answer));
}



void
Account::addSafetyQuestion(const uint8_t id, std::string question)
{
    if (id >= m_safetyQA.capacity())
    {
        // When m_safetyQA is resized, pairs need to be allocated and filled in the appended cells.
        m_safetyQA.resize(id + 1, make_pair("", ""));
    }
    m_safetyQA[id].first.assign(question);
}



void
Account::addSafetyAnswer(const uint8_t id, const string answer)
{
    if (id >= m_safetyQA.capacity())
    {
        // When m_safetyQA is resized, pairs need to be allocated and filled in the appended cells.
        m_safetyQA.resize(id + 1, make_pair("", ""));
        cout << "Resizing m_safetyQA from addSafetyAnswer, which is not expected" << endl;
    }
    m_safetyQA[id].second.assign(answer);
}




void
Account::addMisc(string misc)
{
    m_misc.push_back(misc);
}



uint32_t
Account::getKey(void) const
{
    return m_key;
}



list<string>
Account::getLogins(void) const
{
    return m_logins;
}



string
Account::getWebsite(void) const
{
    return m_website;
}



string
Account::getCurrentPassword(void) const
{
    return m_currentPassword;
}



list<string>
Account::getOldPasswords(void) const
{
    return m_oldPasswords;
}



vector<pair<string, string> >
Account::getSafetyQA(void) const
{
    return m_safetyQA;
}


QStringList
Account::getSafetyQuestions(void) const
{
    QStringList safetyQuestionsList;
    for (uint8_t index = 0; index < m_safetyQA.capacity(); index++)
    {
        safetyQuestionsList.push_back(QString::fromStdString(m_safetyQA[index].first));
    }
    return safetyQuestionsList;
}



string
Account::getSafetyAnswer(const uint8_t index) const
{
    if (index >= m_safetyQA.capacity())
    {
        cout << "Attempt to access a safety answer beyond range: " << unsigned(index)
             << ", available :" << unsigned(m_safetyQA.capacity()) << endl;
        return "";
    }
    return m_safetyQA[index].second;
}



list<string>
Account::getMisc(void) const
{
    return m_misc;
}



bool
operator< (const Account &a, const Account &b)
{
    return a.getWebsite() < b.getWebsite();
}



bool
operator> (const Account &a, const Account &b)
{
    return a.getWebsite() > b.getWebsite();
}



bool
operator== (const Account &a, const Account &b)
{
    return (a.getKey() == b.getKey());
}



Account&
Account::operator=(const Account& other)
{
    if (this != &other)
    {
        // Clearing existing content.
        this->m_logins.clear();
        this->m_misc.clear();
        this->m_oldPasswords.clear();
        this->m_safetyQA.clear();

        // Copying content.
        this->m_key = other.getKey();
        this->m_website = other.getWebsite();
        this->m_currentPassword = other.getCurrentPassword();
        this->m_logins = other.getLogins();
        this->m_oldPasswords = other.getOldPasswords();
        this->m_misc = other.getMisc();
        this->m_safetyQA = other.getSafetyQA();
    }
    return *this;
  }
