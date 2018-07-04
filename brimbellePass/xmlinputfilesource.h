// XmlInputFileSource.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef XMLINPUTFILESOURCE_H
#define XMLINPUTFILESOURCE_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>


class XmlInputFileSource : public QWidget
{
    Q_OBJECT
public:
    explicit XmlInputFileSource(const QString type, const QString path, QWidget *parent = 0);
    QString getPath(void);

signals:
    void pathChanged(const QString &);

public slots:
    /// Sets the path displayed in the path lineEdit field.
    /// @param[in] path The new path.
    void setPath(const QString &path);

private slots:
    void updatePath(const QString &path);

private slots:
    void browse(void);

private:
    QLineEdit lineEditPath;
    QPushButton btnBrowse;
    QString strPath;
    QString strType;


};

#endif // XMLINPUTFILESOURCE_H
