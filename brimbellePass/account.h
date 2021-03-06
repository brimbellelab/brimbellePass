// Account.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <list>
#include <string>
#include <utility>
#include <vector>

#include <QStringList>

class Account
{
public:
    Account(void);
    Account(uint32_t key);
    Account(uint32_t key, std::string website);
    Account(uint32_t key,
            std::string website,
            std::string login,
            std::string currentPassword);
    Account(uint32_t key,
            std::string website,
            std::list<std::string> logins,
            std::string currentPassword,
            std::list<std::string> oldPasswords,
            std::vector<std::pair<std::string, std::string> > safetyQA,
            std::list<std::string> misc);

    void addLogin(std::string newLogin);
    void setCurrentPassword(std::string password);
    void addOldPassword(std::string oldPassword);
    void changeCurrentPassword(std::string newPassword);
    void addSafetyQA(std::string question, std::string answer);
    void addSafetyQuestion(const uint8_t id, const std::string question);
    void addSafetyAnswer(const uint8_t id, const std::string answer);
    void addMisc(std::string misc);
    Account& operator=(const Account& other);

    uint32_t getKey(void) const;
    std::list<std::string> getLogins(void) const;
    std::string getWebsite(void) const;
    std::string getCurrentPassword(void) const;
    std::list<std::string> getOldPasswords(void) const;
    std::vector<std::pair<std::string, std::string>> getSafetyQA(void) const;
    QStringList getSafetyQuestions(void) const;
    std::string getSafetyAnswer(const uint8_t index) const;
    std::list<std::string> getMisc(void) const;

private:
    uint32_t m_key;
    std::string m_website;
    std::list<std::string> m_logins;
    std::string m_currentPassword;
    std::list<std::string> m_oldPasswords;
    std::vector<std::pair<std::string, std::string> > m_safetyQA;
    std::list<std::string> m_misc;
};

bool operator< (const Account &a, const Account &b);
bool operator> (const Account &a, const Account &b);
bool operator== (const Account &a, const Account &b);

#endif // ACCOUNT_H
