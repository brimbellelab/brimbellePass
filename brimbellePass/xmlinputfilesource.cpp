// XmlInputFileSource.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "xmlinputfilesource.h"

#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>

#include <iostream>
XmlInputFileSource::XmlInputFileSource(const QString type, const QString path, QWidget *parent) : QWidget(parent)
{
    strPath = path;
    strType = type;
    QVBoxLayout *layoutMain = new QVBoxLayout;

    QGroupBox *gbMain = new QGroupBox(strType, this);
    QHBoxLayout* layoutGbMain = new QHBoxLayout;
    gbMain->setLayout(layoutGbMain),

    lineEditPath.setText(strPath);
    QObject::connect(&lineEditPath, SIGNAL(textChanged(QString)), this, SIGNAL(pathChanged(QString)));
    QObject::connect(&lineEditPath, SIGNAL(textChanged(QString)), this, SLOT(updatePath(QString)));
    btnBrowse.setText("Browse");
    QObject::connect(&btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));

    layoutGbMain->addWidget(&lineEditPath);
    layoutGbMain->addWidget(&btnBrowse);

    layoutMain->addWidget(gbMain);
    this->setLayout(layoutMain);
}



QString
XmlInputFileSource::getPath(void)
{
    return strPath;
}



void
XmlInputFileSource::browse(void)
{
    //QDir::currentPath()
    QString filePath = QFileDialog::getOpenFileName(this, "Find source file", strPath);
    strPath = filePath;
    lineEditPath.setText(strPath);
}



void
XmlInputFileSource::updatePath(const QString &path)
{
    std::cout << "Path update!" << std::endl;
    strPath = path;
}



void
XmlInputFileSource::setPath(const QString &path)
{
    lineEditPath.setText(path);
}
