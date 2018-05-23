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

public slots:
    void browse(void);

private:
    QLineEdit lineEditPath;
    QPushButton btnBrowse;
    QString strPath;
    QString strType;
};

#endif // XMLINPUTFILESOURCE_H
