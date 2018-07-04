#include "filepathfinder.h"

#include <QFileDialog>
#include <QHBoxLayout>

#include <iostream>

FilePathFinder::FilePathFinder(const QString path, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;
    filePath = path;
    filePathField.setText(filePath);
    QObject::connect(&filePathField, SIGNAL(editingFinished()), this, SLOT(handlePathFieldChanged));

    btnOpenFileDialog.setIconSize(QSize(12, 12));
    btnOpenFileDialog.setIcon(QIcon(":icons/clipboardIco24.png")); // TODO change icon for an "open file".
    QObject::connect(&btnOpenFileDialog, SIGNAL(clicked()), this, SLOT(openFileDialog()));

    layout->addWidget(&filePathField);
    layout->addWidget(&btnOpenFileDialog);
    this->setLayout(layout);
}



void
FilePathFinder::setText(const QString text)
{
    filePath = text;
    filePathField.setText(filePath);
}



QString
FilePathFinder::text(void)
{
    return filePathField.text();
}



void
FilePathFinder::openFileDialog(void)
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString strFile = dialog.getSaveFileName(NULL, "Create New File","","");
    filePath = strFile;
    filePathField.setText(strFile);

}



void
FilePathFinder::handlePathFieldChanged(void)
{
    // Check if there's an actual change.
    if (filePathField.text() != filePath)
    {
        std::cout << "Path field changed" << std::endl;
        filePath = filePathField.text();
        emit pathChanged();
    }
}
