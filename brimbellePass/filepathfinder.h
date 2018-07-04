#ifndef FILEPATHFINDER_H
#define FILEPATHFINDER_H

#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>

class FilePathFinder : public QWidget
{
    Q_OBJECT
public:
    explicit FilePathFinder(const QString path = "", QWidget *parent = 0);

    void setText(const QString text);
    QString text(void);

signals:
    /// Triggered when the path field has been edited.
    void pathChanged(void);

private slots:
    void openFileDialog(void);
    void handlePathFieldChanged(void);

private:
    QLineEdit filePathField;
    QPushButton btnOpenFileDialog;
    QString filePath;
};

#endif // FILEPATHFINDER_H
