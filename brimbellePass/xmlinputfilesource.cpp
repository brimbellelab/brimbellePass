#include "xmlinputfilesource.h"

#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>

#include <iostream>
XmlInputFileSource::XmlInputFileSource(const QString type, const QString path, QWidget *parent) : QWidget(parent)
{
    strPath = path;
    strType = type;

    QGroupBox *gbMain = new QGroupBox(strType, this);
    QHBoxLayout* layoutMain = new QHBoxLayout;
    gbMain->setLayout(layoutMain),

    lineEditPath.setText(strPath);
    QObject::connect(&lineEditPath, SIGNAL(textChanged(QString)), this, SIGNAL(pathChanged(QString)));
    QObject::connect(&lineEditPath, SIGNAL(textChanged(QString)), this, SLOT(updatePath(QString)));
    btnBrowse.setText("Browse");
    QObject::connect(&btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));

    layoutMain->addWidget(&lineEditPath);
    layoutMain->addWidget(&btnBrowse);

    //this->setLayout(layout);
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
    std::cout << "PATH Updated from " << strPath.toStdString() << " to " << path.toStdString() << std::endl;
    strPath = path;
}

