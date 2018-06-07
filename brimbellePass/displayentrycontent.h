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

class DisplayEntryContent : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayEntryContent(QWidget *parent = 0);
    void update(const Account *account);

signals:

public slots:
    /// Trigger the UI to move the "current password" to "old passwords" and generate a new one.
    void changePassword(void);

    /// Trigger the save of any changes made to this entry.
    void saveChanges(void);

    // Update the content of the safety answer field.
    // @param[in] index Index of the safety answer to be loaded.
    void updateSafetyAnswerField(const int index);

private:
    static const int defaultMargin = 5;
    Account currentAccount;
    QLineEdit *lineEditWebsite;
    QGroupBox *gbLogins;
    QVBoxLayout *layoutLogins;
    QVector<QLineEdit*> entryLineLogins;
    QGroupBox *gbCurrentPassword;
    PasswordEntryLine *entryLineCurrentPassword;
    QPushButton *btnNewPassword;
    QGroupBox *gbOldPasswords;
    QVBoxLayout *layoutOldPasswords;
    QVector<PasswordEntryLine*> entryLineOldPasswords;
    QGroupBox *gbSafetyQA;
    QComboBox *comboBoxSafetyQuestion;
    PasswordEntryLine *safetyAnswer;
    QTextEdit *textEditMisc;
    QPushButton *btnEditEntry;
    Cipher cipherEngine;
};

#endif // DISPLAYENTRYCONTENT_H
