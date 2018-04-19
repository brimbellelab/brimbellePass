#include "displayentrycontent.h"

#include <QVBoxLayout>

DisplayEntryContent::DisplayEntryContent(QWidget *parent) : QWidget(parent)
{
    lineEditWebsite = new QLineEdit("www.mybank.com");

    gbLogins = new QGroupBox("Logins", this);
    login = new QLineEdit("Moi@gmail.com");
    //login = new QLineEdit("123456789", gbLogin);
    QVBoxLayout *layoutLogins = new QVBoxLayout;
    layoutLogins->addWidget(login);
    gbLogins->setLayout(layoutLogins),

    gbCurrentPassword = new QGroupBox("Current password");
    entryLineCurrentPassword = new PasswordEntryLine("H4ck3erz", this);
    btnNewPassword = new QPushButton("New password", this);
    QObject::connect(btnNewPassword, SIGNAL(clicked()), this, SLOT(changePassword()));
    QVBoxLayout *layoutCurrentPassword = new QVBoxLayout;
    layoutCurrentPassword->addWidget(entryLineCurrentPassword);
    layoutCurrentPassword->addWidget(btnNewPassword);
    gbCurrentPassword->setLayout(layoutCurrentPassword);

    gbOldPasswords = new QGroupBox("Old passwords");
 //   entryLineOldPasswords = new QVector<PasswordEntryLine>(0);
 //   entryLineOldPasswords->push_back(PasswordEntryLine("H4ck3erz", this));
    QVBoxLayout *layoutOldPasswords = new QVBoxLayout;
 //   layoutOldPasswords->addWidget(entryLineOldPasswords);
    gbOldPasswords->setLayout(layoutOldPasswords);

    textEditMisc = new QTextEdit("Do not access from abroad or it will lock my account!");

    btnEditEntry = new QPushButton("Save changes", this);
    QObject::connect(btnEditEntry, SIGNAL(clicked()), this, SLOT(saveChanges()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEditWebsite);
    layout->addWidget(gbLogins);
    layout->addWidget(gbCurrentPassword);
    layout->addWidget(gbOldPasswords);
    layout->addWidget(textEditMisc);
    layout->addWidget(btnEditEntry);

    this->setLayout(layout);
}



void
DisplayEntryContent::changePassword(void)
{
    ;
}



void
DisplayEntryContent::saveChanges(void)
{
    ;
}
