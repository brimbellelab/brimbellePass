#include "account.h"

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
        list<pair<string, string> > safetyQA,
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



list<pair<string, string> >
Account::getSafetyQA(void) const
{
    return m_safetyQA;
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

