#include "xmlinputfilesource.h"

#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>


XmlInputFileSource::XmlInputFileSource(const QString type, const QString path, QWidget *parent) : QWidget(parent)
{
    strPath = path;
    strType = type;

    QGroupBox *gbMain = new QGroupBox(strType, this);
    QHBoxLayout* layoutMain = new QHBoxLayout;
    gbMain->setLayout(layoutMain),

    lineEditPath.setText(strPath);
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
