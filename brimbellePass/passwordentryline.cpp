#include "passwordentryline.h"

#include <QApplication>
#include <QClipboard>

PasswordEntryLine::PasswordEntryLine(const QString password, QWidget *parent) : QWidget(parent)
{
    strPassword = new QString(password);

    lineEditPassword = new QLineEdit(this);
    lineEditPassword->setText(*strPassword);
    lineEditPassword->setEchoMode(QLineEdit::Password);
    lineEditPassword->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    btnCopy = new QPushButton("Cp", this);
    QObject::connect(btnCopy, SIGNAL(clicked()), this, SLOT(addPasswordToClipboard()));

    checkboxPasswordHidden = new QCheckBox("Hide", this);
    checkboxPasswordHidden->setCheckState(Qt::CheckState::Checked);
    QObject::connect(checkboxPasswordHidden, SIGNAL(clicked(bool)), this, SLOT(setFieldAsPassword(bool)));

    layout = new QGridLayout();
    layout->addWidget(lineEditPassword, 0, 0);
    layout->addWidget(btnCopy, 0, 1);
    layout->addWidget(checkboxPasswordHidden, 0, 2);

    this->setLayout(layout);
}



void
PasswordEntryLine::setFieldAsPassword(bool hide)
{
    if (hide)
    {
        lineEditPassword->setEchoMode(QLineEdit::Password);
    }
    else
    {
        lineEditPassword->setEchoMode(QLineEdit::Normal);
    }
}



void
PasswordEntryLine::addPasswordToClipboard(void)
{
    //QClipboard::setText("pouet");
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(*this->strPassword, QClipboard::Clipboard);
}



PasswordEntryLine::~PasswordEntryLine()
{
    delete lineEditPassword;
    delete btnCopy;
    delete checkboxPasswordHidden;
    delete layout;
    delete strPassword;
}
