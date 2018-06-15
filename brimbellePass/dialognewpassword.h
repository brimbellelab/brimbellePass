// DialogNewPassword.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef DIALOGNEWPASSWORD_H
#define DIALOGNEWPASSWORD_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class DialogNewPassword : public QDialog
{
    Q_OBJECT
public:
    explicit DialogNewPassword(QWidget *parent = 0);

    // Retrieve the new password from the DialogNewPassword.
    // @return The new password approved, not crypted.
    QString data(void);
signals:

public slots:

private slots:
    void showPasswordText(bool show);
    void testAndReturn(void);

private:
    QLineEdit* newPasswordField;
    QLabel* confirmNewPasswordLabel;
    QLineEdit* confirmNewPasswordField;
    QCheckBox* showPassword;
    QPushButton* btnOk;
    QString newPassword;
};

#endif // DIALOGNEWPASSWORD_H
