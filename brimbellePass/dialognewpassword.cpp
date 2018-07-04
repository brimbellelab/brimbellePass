// DialogNewPassword.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "dialognewpassword.h"

#include <QMessageBox>
#include <QSizePolicy>
#include <QObject>

DialogNewPassword::DialogNewPassword(QWidget *parent) : QDialog(parent)
{
    QLabel* newPasswordLabel = new QLabel("New Password");
    newPasswordField = new QLineEdit("");
    newPasswordField->setEchoMode(QLineEdit::Password);
    newPasswordField->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    confirmNewPasswordLabel = new QLabel("Retype password");
    confirmNewPasswordField = new QLineEdit("");
    confirmNewPasswordField->setEchoMode(QLineEdit::Password);
    confirmNewPasswordField->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    showPassword = new QCheckBox("Show password");
    btnOk = new QPushButton("Ok");

    QObject::connect(showPassword, SIGNAL(toggled(bool)), this, SLOT(showPasswordText(bool)));
    QObject::connect(btnOk, SIGNAL(clicked()), this, SLOT(testAndReturn()));

    layout = new QVBoxLayout;
    layout->addWidget(newPasswordLabel);
    layout->addWidget(newPasswordField);
    layout->addWidget(confirmNewPasswordLabel);
    layout->addWidget(confirmNewPasswordField);
    layout->addWidget(showPassword);
    layout->addWidget(btnOk);

    // Avoid rearranging the layout when masking the confirm answer widgets.
    QSizePolicy retainSizeConfirmPasswordField = confirmNewPasswordField->sizePolicy();
    retainSizeConfirmPasswordField.setRetainSizeWhenHidden(true);
    confirmNewPasswordField->setSizePolicy(retainSizeConfirmPasswordField);

    QSizePolicy retainSizeConfirmPasswordLabel = confirmNewPasswordLabel->sizePolicy();
    retainSizeConfirmPasswordLabel.setRetainSizeWhenHidden(true);
    confirmNewPasswordLabel->setSizePolicy(retainSizeConfirmPasswordLabel);

    this->setLayout(layout);
}



void
DialogNewPassword::showPasswordText(bool show)
{
    if (show && (newPasswordField->echoMode() == QLineEdit::Password))
    {
        newPasswordField->setEchoMode(QLineEdit::Normal);
        confirmNewPasswordLabel->setVisible(false);
        confirmNewPasswordField->setVisible(false);
    }
    else if (!show && newPasswordField->echoMode() != QLineEdit::Password)
    {
        newPasswordField->setEchoMode(QLineEdit::Password);
        confirmNewPasswordLabel->setVisible(true);
        confirmNewPasswordField->setVisible(true);
    }
}



void
DialogNewPassword::testAndReturn(void)
{
    // Start by checking that the 2 fields are the same when the showAnswer is not checked.
    if (showPassword->checkState() != Qt::CheckState::Checked)
    {
        if (newPasswordField->text() != confirmNewPasswordField->text())
        {
            // Prepare data to have it ready
            QMessageBox::warning(this, "Passwords mismatch", "The 2 passwords are different");
            return;
        }
    }
    // Check that the password field is not empty.
    if (newPasswordField->text().isEmpty())
    {
        QMessageBox::warning(this, "Password empty", "The password field can't be empty");
        return;
    }
    newPassword = newPasswordField->text();
    this->accept();
}



QString
DialogNewPassword::password(void)
{
    return newPassword;
}
