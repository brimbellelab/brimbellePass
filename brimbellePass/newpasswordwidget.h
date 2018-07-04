// NewPasswordWidget.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef NEWPASSWORDWIDGET_H
#define NEWPASSWORDWIDGET_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

enum class NewPasswordWidgetStatus
{
    passwordValid,
    passwordEmpty,
    passwordsMismatch
};



class NewPasswordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewPasswordWidget(QWidget *parent = 0);

    // Retrieve the new password from the DialogNewPassword.
    // @return The new password approved, not crypted.
    // @throws NewPasswordWidgetStatus if trying to fetch invalid data.
    QString data(void);

    /// Get the current status of the NewPasswordWidget.
    /// @returns NewPasswordWidgetStatus if trying to fetch invalid data.
    NewPasswordWidgetStatus getStatus(void);

    /// Check if the password enter is valid.
    /// @returns \c true if valid, \c false otherwise.
    bool isPasswordValid(void);

    /// Displays a message box detailing a NewPasswordWidgetStatus.
    /// @param[in] status A member of NewPasswordWidgetStatus, for instance the exception thrown by data().
    void displayMessageBoxStatus(NewPasswordWidgetStatus status);

signals:

public slots:

private slots:
    void showPasswordText(bool show);

private:
    QVBoxLayout* layout;
    QLineEdit* newPasswordField;
    QLabel* confirmNewPasswordLabel;
    QLineEdit* confirmNewPasswordField;
    QCheckBox* showPassword;
};

#endif // NEWPASSWORDWIDGET_H
