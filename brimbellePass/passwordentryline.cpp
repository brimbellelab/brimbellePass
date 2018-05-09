#include "passwordentryline.h"

#include <QApplication>
#include <QClipboard>
#include <QIcon>
#include <QStyle>

#include <iostream>

PasswordEntryLine::PasswordEntryLine()
{
    PasswordEntryLine("");
}



PasswordEntryLine::PasswordEntryLine(const QString password, QWidget *parent) : QWidget(parent)
{
    strPassword = password;

    lineEditPassword.setText(strPassword);
    lineEditPassword.setEchoMode(QLineEdit::Password);
    lineEditPassword.setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    btnCopy.setIconSize(QSize(12, 12));
    btnCopy.setIcon(QIcon(":icons/clipboardIco24.png"));
    QObject::connect(&btnCopy, SIGNAL(clicked()), this, SLOT(addPasswordToClipboard()));

    checkboxPasswordHidden.setText("Hide");
    checkboxPasswordHidden.setCheckState(Qt::CheckState::Checked);
    QObject::connect(&checkboxPasswordHidden, SIGNAL(clicked(bool)), this, SLOT(setFieldAsPassword(bool)));

    layout.addWidget(&lineEditPassword, 0, 0);
    layout.addWidget(&btnCopy, 0, 1);
    layout.addWidget(&checkboxPasswordHidden, 0, 2);

    this->setLayout(&layout);
}



void
PasswordEntryLine::setText(const QString text)
{
    strPassword = text;
    lineEditPassword.setText(strPassword);
}



void
PasswordEntryLine::setFieldAsPassword(bool hide)
{
    if (hide)
    {
        lineEditPassword.setEchoMode(QLineEdit::Password);
    }
    else
    {
        lineEditPassword.setEchoMode(QLineEdit::Normal);
    }
}



void
PasswordEntryLine::addPasswordToClipboard(void)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(this->strPassword, QClipboard::Clipboard);
}
