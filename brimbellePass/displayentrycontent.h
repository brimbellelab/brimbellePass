#ifndef DISPLAYENTRYCONTENT_H
#define DISPLAYENTRYCONTENT_H

#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>
#include <QWidget>

#include "passwordentryline.h"

class DisplayEntryContent : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayEntryContent(QWidget *parent = 0);

signals:

public slots:
    /// Trigger the UI to move the "current password" to "old passwords" and generate a new one.
    void changePassword(void);

    /// Trigger the save of any changes made to this entry.
    void saveChanges(void);

private:
    QLineEdit *lineEditWebsite;
    QGroupBox *gbLogins;
    QLineEdit *login;
    QGroupBox *gbCurrentPassword;
    PasswordEntryLine *entryLineCurrentPassword;
    QPushButton *btnNewPassword;
    QGroupBox *gbOldPasswords;
    QVector<PasswordEntryLine> *entryLineOldPasswords;
    QTextEdit *textEditMisc;
    QPushButton *btnEditEntry;
};

#endif // DISPLAYENTRYCONTENT_H
