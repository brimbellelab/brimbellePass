// Cipher.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

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
    ~Cipher();

    /// Set the user password / AES key that will be used to decrypt infos.
    /// @param[in] mainPassword The user password. Can be any string.
    /// @note As the cipher engine uses AES256, the AES key is 32 bytes long. If the password is shorter than 32, it
    /// will be extended to 32 bytes with the character '0'. If it's longer than 32 bytes, the password will be
    /// truncated.
    void setPassword(const QString& mainPassword);

    /// Encrypt a string with the current user password as AES key.
    /// @param[in] inputPlainString The string to encrypt, in generic UTF8 QString format.
    /// @return The ciphered string in base64, UTF8 format.
    /// @throw An std::runtime_error if comething went wrong.
    QString encrypt(QString inputPlainString);

    /// Decrypt a string with the current user password as AES key.
    /// @param[in] inputCryptedString The AES ciphered string to decrypt, in Base64, UTF8 QString format.
    /// @return The deciphered string in UTF8 format.
    /// @throw An std::runtime_error if comething went wrong.
    QString decrypt(QString inputCryptedString);

private:
    static constexpr size_t KEY_SIZE = 32; // AES256 key size.
    static constexpr size_t BLOCK_SIZE = 16; // AES256 block size.
    QString mainUserPassword; // Password as entered by the user, without the byte padding to match a 32 bytes length key.
    unsigned char aesKey[KEY_SIZE]; // AES key based on the user password, that will be used to encrypt/decrypt.
    // Default AES initialisation vector.
    // TODO should be possible to export/import a custom value, stored in the logins xml file?
    unsigned char iv[BLOCK_SIZE] = {'1' ,'3' ,'4' ,'6' ,'7' ,'9' ,'8' ,'2' ,'5' ,'0' ,'1' ,'9' ,'7' ,'3' ,'0' ,'0'};
};

#endif // CYPHER_H
