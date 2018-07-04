// DialogNewDatabase.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef DIALOGNEWDATABASE_H
#define DIALOGNEWDATABASE_H

#include "filepathfinder.h"
#include "newpasswordwidget.h"

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

class DialogNewDatabase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogNewDatabase(QWidget *parent = 0);

    /// Retrieve the new logins file path from the DialogNewDatabase.
    /// @return The new logins file path.
    /// @throws QString "Invalid data" if the logins path is not available.
    QString loginsPath(void);

    /// Retrieve the new passwords file path from the DialogNewDatabase.
    /// @return The new passwords file path.
    /// @throws QString "Invalid data" if the passwords path is not available.
    QString passwordsPath(void);

    /// Retrieve the new password from the DialogNewDatabase.
    /// @return The new passwords, unciphered.
    /// @throws QString "Invalid data" if the new password is not available.
    QString newPassword(void);

    /// Check if the data content is valid and can be retrieved.
    /// @returns \c true if data can be retrieved with getter, \c false otherwise.
    bool isDataValid(void);

signals:

public slots:
    void testAndReturn(void);

private:
    bool dataValid = false;
    QLabel labelLoginsFile;
    FilePathFinder loginFileFinder;
    QLabel labelPasswordsFile;
    FilePathFinder passwordFileFinder;
    NewPasswordWidget newPasswordWidget;
    QPushButton btnOk;
    QString newPwd;
    QString loginsFilePath;
    QString passwordsFilePath;
};

#endif // DIALOGNEWDATABASE_H
