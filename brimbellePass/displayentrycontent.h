// DisplayEntryContent.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef DISPLAYENTRYCONTENT_H
#define DISPLAYENTRYCONTENT_H

#include "account.h"
#include "cipher.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "passwordentryline.h"
#include "safetyqawidget.h"

class DisplayEntryContent : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayEntryContent(QWidget *parent = 0);
    void update(const Account *account);

    /// Trigger the save of any changes made to this entry.
    /// @param[in] accountToSave An account object that will be filled with the content of this entry.
    /// @note accountToSave must have its key parameter set prior to be passed to the function.
    void saveChanges(Account &accountToSave);

    /// Retrieve the current AccountKey.
    /// @note Make sure that there is actually a meaningful account loaded before calling.
    uint32_t getCurrentAccountKey(void);

    /// Erase content of all fields.
    void clearContent(void);

signals:

public slots:
    /// Add a login field if there's no empty login field already available.
    void addLogin();

    /// Trigger the UI to move the "current password" to "old passwords" and generate a new one.
    void changePassword(void);

private:
    static const int defaultMargin = 5;
    Account currentAccount;
    QGroupBox *gbLogins;
    QVBoxLayout *layoutLogins;
    QVector<QLineEdit*> entryLineLogins;
    QGroupBox *gbCurrentPassword;
    PasswordEntryLine *entryLineCurrentPassword;
    QPushButton *btnNewPassword;
    QGroupBox *gbOldPasswords;
    QVBoxLayout *layoutOldPasswords;
    QVector<PasswordEntryLine*> entryLineOldPasswords;
    SafetyQAWidget *safetyQA;
    QTextEdit *textEditMisc;
    Cipher cipherEngine;
};

#endif // DISPLAYENTRYCONTENT_H
