// DialogOpenDatabase.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef DIALOGOPENDATABASE_H
#define DIALOGOPENDATABASE_H

#include "xmlinputfilesource.h"

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>

class DialogOpenDatabase : public QDialog
{
    Q_OBJECT
public:
    explicit DialogOpenDatabase(QWidget *parent = 0);

    /// Retrieve the new logins file path from the DialogOpenDatabase.
    /// @return The new logins file path.
    /// @throws QString "Invalid data" if the logins path is not available.
    QString loginsPath(void);

    /// Retrieve the new passwords file path from the DialogOpenDatabase.
    /// @return The new passwords file path.
    /// @throws QString "Invalid data" if the passwords path is not available.
    QString passwordsPath(void);

    /// Check if the data content is valid and can be retrieved.
    /// @returns \c true if data can be retrieved with getter, \c false otherwise.
    bool isDataValid(void);

signals:

public slots:
    void testAndReturn(void);

private:
    bool dataValid = false;
    XmlInputFileSource* loginFileFinder;
    XmlInputFileSource* passwordFileFinder;
    QPushButton btnOk;
    QString loginsFilePath;
    QString passwordsFilePath;
};

#endif // DIALOGOPENDATABASE_H
