// AccountsBook.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "accountsbook.h"

#include "configfile.h"
#include "xmldom.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <QString>

using namespace std;

AccountsBook::AccountsBook(void)
{
    ;
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
                else if(entryChild.tagName() == "safetyQuestion")
                {
                    auto index = entryChild.attribute("index", "0").toUInt();
                    string safetyQuestion = entryChild.firstChild().toText().data().toStdString();
                    account->addSafetyQuestion(index, safetyQuestion);
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
                    else if(entryChild.tagName() == "safetyAnswer")
                    {
                        auto index = entryChild.attribute("index", "0").toUInt();
                        string safetyAnswer = entryChild.firstChild().toText().data().toStdString();
                        account->addSafetyAnswer(index, safetyAnswer);
                    }
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
    // TODO free associated memory!
     m_book.erase(m_book.find(getAccountPointer(accountKey)));
}



void
AccountsBook::deleteAccount(const string website)
{
    // TODO free associated memory!
    m_book.erase(m_book.find(getAccountPointer(website)));
}



const Account*
AccountsBook::getAccount(const uint32_t accountKey) const
{
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



const set<uint32_t>
AccountsBook::getKeysList(void)
{
    set<uint32_t> keysList;
    set<Account*>::iterator it;
    for (it = m_book.begin(); it != m_book.end(); ++it)
    {
        keysList.insert((**it).getKey());
    }
    return keysList;
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



uint32_t
AccountsBook::getAvailableKey(void)
{
    // Get a sorted list of account keys.
    set<uint32_t> keysList = getKeysList();

    // First check if there's an empty spot in the current accountsBook.
    // It's sorted so if the last element is equal to the number of elements, there's no available room.
    uint32_t lastKey = *(--(keysList.cend()));
    if (keysList.size()  == lastKey)
    {
        return lastKey + 1;
    }

    // If we reach here, there's an available spot.
    set<uint32_t>::iterator it = keysList.begin();
    uint32_t previousValue = *it;

    if (previousValue > 1)
    {
        // The first element of the list is above the minimum value, so there's an empty spot in front.
        return 1;
    }

    ++it;
    for (; it != keysList.end(); ++it)
    {
        if ((*it) > previousValue + 1)
        {
            return previousValue + 1;
        }
        previousValue = *it;
    }
    throw string("No value found");
}



void
AccountsBook::saveAccountsBookToXML(void)
{
    // Fetch XML Files path.
    ConfigFile configFile;

    // Open files.
    QFile loginsXmlFile(configFile.getLoginsFilePath());
    QFile passwordsXmlFile(configFile.getPasswordsFilePath());

    if ((loginsXmlFile.open(QIODevice::WriteOnly)) && passwordsXmlFile.open(QIODevice::WriteOnly))
    {
        // Generate XML structure;
        QDomDocument loginsDom("loginList");
        QDomDocument passwordsDom("pwdList");

        // Root element.
        QDomElement loginListElement = loginsDom.createElement("loginList");
        loginsDom.appendChild(loginListElement);

        // It seems like a good idea to add the version of the engine as an attribute.
        loginListElement.setAttribute("version", "1.0");

        // Root element of password
        QDomElement pwdListElement = passwordsDom.createElement("pwdList");
        passwordsDom.appendChild(pwdListElement);

        set<Account*>::iterator it;
        for (it = m_book.begin(); it != m_book.end(); ++it)
        {
            // Entry element AKA account.
            // To logins file.
            QDomElement entryElement = loginsDom.createElement("entry");
            loginListElement.appendChild(entryElement);
            entryElement.setAttribute("id", QString::number((**it).getKey()));
            entryElement.setAttribute("website", QString::fromStdString((**it).getWebsite()));

            //To passwords file.
            QDomElement pwdEntryElement = passwordsDom.createElement("entry");
            pwdListElement.appendChild(pwdEntryElement);
            pwdEntryElement.setAttribute("id", QString::number((**it).getKey()));

            // Logins
            list<string> logins = (**it).getLogins();
            list<string>::iterator itLogins;
            for (itLogins = logins.begin(); itLogins != logins.end(); ++itLogins)
            {
                QDomElement loginElement = loginsDom.createElement("login");
                entryElement.appendChild(loginElement);
                QDomText loginValue = loginsDom.createTextNode(QString::fromStdString(*itLogins));
                loginElement.appendChild(loginValue);
            }

            // Current password.
            QDomElement passwordElement = passwordsDom.createElement("password");
            pwdEntryElement.appendChild(passwordElement);
            QDomText passwordValue = passwordsDom.createTextNode(QString::fromStdString((*it)->getCurrentPassword()));
            passwordElement.appendChild(passwordValue);

            // Old password.
            list<string> oldPasswords = (**it).getOldPasswords();
            list<string>::iterator itOldPasswords;
            for (itOldPasswords = oldPasswords.begin(); itOldPasswords != oldPasswords.end(); ++itOldPasswords)
            {
                QDomElement oldPasswordElement = passwordsDom.createElement("oldPassword");
                pwdEntryElement.appendChild(oldPasswordElement);
                QDomText oldPasswordValue = passwordsDom.createTextNode(QString::fromStdString(*itOldPasswords));
                oldPasswordElement.appendChild(oldPasswordValue);
            }

            // Safety questions/answers.
            int indexQA = 0;
            for (pair<string, string> qa: (*it)->getSafetyQA())
            {
                // Safety question.
                QDomElement safetyQuestionElement = loginsDom.createElement("safetyQuestion");
                entryElement.appendChild(safetyQuestionElement);
                safetyQuestionElement.setAttribute("index", QString::number(indexQA));
                QDomText safetyQuestionValue = loginsDom.createTextNode(QString::fromStdString(qa.first));
                safetyQuestionElement.appendChild(safetyQuestionValue);

                // Safety answer.
                QDomElement safetyAnswerElement = passwordsDom.createElement("safetyAnswer");
                pwdEntryElement.appendChild(safetyAnswerElement);
                safetyAnswerElement.setAttribute("index", QString::number(indexQA));
                QDomText safetyAnswerValue = passwordsDom.createTextNode(QString::fromStdString(qa.second));
                safetyAnswerElement.appendChild(safetyAnswerValue);

                // Don't forget to increment the index.
                indexQA++;
            }

            // Misc.
            list<string> misc = (**it).getMisc();
            list<string>::iterator itMisc;
            for (itMisc = misc.begin(); itMisc != misc.end(); ++itMisc)
            {
                QDomElement miscElement = loginsDom.createElement("misc");
                entryElement.appendChild(miscElement);
                QDomText miscValue = loginsDom.createTextNode(QString::fromStdString(*itMisc));
                miscElement.appendChild(miscValue);
            }
        }

        // Writing the DOM into the logins file.
        QString loginsDomString = loginsDom.toString();
        QTextStream writeLoginsFileStream(&loginsXmlFile);
        writeLoginsFileStream << loginsDomString;

        // Writing the DOM into the passwords file.
        QString passwordsDomString = passwordsDom.toString();
        QTextStream writePasswordsFileStream(&passwordsXmlFile);
        writePasswordsFileStream << passwordsDomString;
    }
    else
    {
        // QMessageBox::warning(this, "Create Login file", "The Login database file couldn't be saved");
        throw QString("The database files couldn't be saved");
    }
    loginsXmlFile.close();
    passwordsXmlFile.close();
}



ostream& operator<< (ostream& os, const AccountsBook& accountBook)
{
    accountBook.displayWebsiteList(os);
    return os;
}
