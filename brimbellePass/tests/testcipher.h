// testcipher.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#pragma once

#include <QtTest/QtTest>


class TestCipher: public QObject
{
    Q_OBJECT
private slots:

    /// Test encrypting.
    void encrypt_data(void);
    void encrypt(void);

    /// Test decrypting.
    void decrypt_data(void);
    void decrypt(void);

    // Do encryption and decryption in one pass.
    void encryptAndDecrypt_data(void);
    void encryptAndDecrypt(void);
};
