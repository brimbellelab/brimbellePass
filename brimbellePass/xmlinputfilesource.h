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

private slots:
    void browse(void);
    void updatePath(const QString &path);

private:
    QLineEdit lineEditPath;
    QPushButton btnBrowse;
    QString strPath;
    QString strType;


};

#endif // XMLINPUTFILESOURCE_H
