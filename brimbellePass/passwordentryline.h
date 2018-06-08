// PasswordEntryLine.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef PASSWORDENTRYLINE_H
#define PASSWORDENTRYLINE_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QString>
#include <QWidget>

class PasswordEntryLine : public QWidget
{
    Q_OBJECT
public:
    explicit PasswordEntryLine();
    explicit PasswordEntryLine(const QString password, QWidget *parent = 0);
    void setText(const QString text);

signals:

public slots:
    /// Hide the content of the text field, or show password.
    /// @param[in] hide: \ctrue Hide field;\cfalse Show password.
    void setFieldAsPassword(bool hide);

    /// Copy the current password into the clipboard.
    void addPasswordToClipboard(void);

private:
    static const int defaultMargin = 5;
    QLineEdit lineEditPassword;
    QToolButton btnCopy;
    QCheckBox checkboxPasswordHidden;
    QGridLayout layout;
    QString strPassword;
};

#endif // PASSWORDENTRYLINE_H
