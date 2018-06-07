#ifndef CYPHER_H
#define CYPHER_H

#include <QObject>
#include <QString>



#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/evp.h>

class Cipher
{
public:
    Cipher();
    Cipher(QString mainPassword);

    void setPassword(const QString& mainPassword);
    QByteArray encrypt(QByteArray input);
    QByteArray decrypt(QByteArray input);

private:
    static constexpr size_t KEY_SIZE = 32;
    static constexpr size_t BLOCK_SIZE = 16;
    QString key;
    unsigned char aesKey[KEY_SIZE];
    unsigned char iv[BLOCK_SIZE] = {'1' ,'3' ,'4' ,'6' ,'7' ,'9' ,'8' ,'2' ,'5' ,'0' ,'1' ,'9' ,'7' ,'3' ,'0' ,'0'};
};

#endif // CYPHER_H
