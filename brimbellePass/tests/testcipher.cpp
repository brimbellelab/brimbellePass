// testcipher.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include <QtTest/QtTest>

#include "testcipher.h"
#include "../cipher.h"

// Needed to make the data test engine aware of type Cipher.
Q_DECLARE_METATYPE(Cipher);

void
TestCipher::encrypt_data(void)
{
    QTest::addColumn<QString>("plainString");
    QTest::addColumn<QString>("encryptedString");
    QTest::addColumn<Cipher>("cipherEngine");

    Cipher cipherGUEST;
    cipherGUEST.setPassword("GUEST");

    Cipher cipher10;
    cipher10.setPassword("0123456789");

    Cipher cipherLongPassword;
    cipherLongPassword.setPassword("Lorem ipsum dolor sit amet, consectetur adipiscing elit");

    QTest::newRow("Zero length string (pwd: GUEST)")
            << ""
            << "U1c9+4WMRkmGwp4dJlMF/g=="
            << cipherGUEST;
    QTest::newRow("15 char string (pwd: GUEST)")
            << "012345678901234"
            << "OCvHw7pfPV+6eu61V+y7Hw=="
            << cipherGUEST;
    QTest::newRow("16 char string (pwd: GUEST)")
            << "0123456789012345"
            << "bpP+6U8CdbNEkL6YgXFbE1+WIT6FfrelpMokkq9hxfQ="
            << cipherGUEST;
    QTest::newRow("17 char string (pwd: GUEST)")
            << "lorem ipsum dolor"
            << "cq34aDfET0cjTrTqh6QBqz9tmf25ecm1km5fg7CaMZU="
            << cipherGUEST;

    QTest::newRow("Zero length string (pwd: 0123456789)")
            << ""
            << "XRapi1DWQ4vjXEeNu4DGFA=="
            << cipher10;
    QTest::newRow("15 char string (pwd: 0123456789)")
            << "012345678901234"
            << "2f98RNTsds88CDAtV0L9oA=="
            << cipher10;
    QTest::newRow("16 char string (pwd: 0123456789)")
            << "0123456789012345"
            << "V72Y/mhDjHuahrwo24olMLWz3KVIb8sbiO3KwpcJmPw="
            << cipher10;
    QTest::newRow("17 char string (pwd: 0123456789)")
            << "lorem ipsum dolor"
            << "F/Hu2ajWHBp9vpt+9Jb1Bjg/QfwD5Vvqpz/HeBMPZ1s="
            << cipher10;

    QTest::newRow("Zero length string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << ""
            << "Af5kxa4xk7Zg6/ussZpHoQ=="
            << cipherLongPassword;
    QTest::newRow("15 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "012345678901234"
            << "jJPklJTCC15wFuQP7RLQtg=="
            << cipherLongPassword;
    QTest::newRow("16 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "0123456789012345"
            << "xu4SjRcX3LtNmM2U03x9hMT8zvKYit3ahcqJeEfAUcU="
            << cipherLongPassword;
    QTest::newRow("17 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "lorem ipsum dolor"
            << "vQWfizjcInX1u6BBTvtTaRsnZaOvSmwi/3pcv3t5EHs="
            << cipherLongPassword;
}

void
TestCipher::encrypt(void)
{
    QFETCH(QString, plainString);
    QFETCH(QString, encryptedString);
    QFETCH(Cipher, cipherEngine);

    QCOMPARE(cipherEngine.encrypt(plainString), encryptedString);
}



void
TestCipher::decrypt_data(void)
{
    QTest::addColumn<QString>("encryptedString");
    QTest::addColumn<QString>("decryptedString");
    QTest::addColumn<Cipher>("cipherEngine");

    Cipher cipherGUEST;
    cipherGUEST.setPassword("GUEST");

    Cipher cipher10;
    cipher10.setPassword("0123456789");

    Cipher cipherLongPassword;
    cipherLongPassword.setPassword("Lorem ipsum dolor sit amet, consectetur adipiscing elit");

    QTest::newRow("Zero length string (pwd: GUEST)")
            << "U1c9+4WMRkmGwp4dJlMF/g=="
            << ""
            << cipherGUEST;
    QTest::newRow("15 char string (pwd: GUEST)")
            << "OCvHw7pfPV+6eu61V+y7Hw=="
            << "012345678901234"
            << cipherGUEST;
    QTest::newRow("16 char string (pwd: GUEST)")
            << "bpP+6U8CdbNEkL6YgXFbE1+WIT6FfrelpMokkq9hxfQ="
            << "0123456789012345"
            << cipherGUEST;
    QTest::newRow("17 char string (pwd: GUEST)")
            << "cq34aDfET0cjTrTqh6QBqz9tmf25ecm1km5fg7CaMZU="
            << "lorem ipsum dolor"
            << cipherGUEST;

    QTest::newRow("Zero length string (pwd: 0123456789)")
            << "XRapi1DWQ4vjXEeNu4DGFA=="
            << ""
            << cipher10;
    QTest::newRow("15 char string (pwd: 0123456789)")
            << "2f98RNTsds88CDAtV0L9oA=="
            << "012345678901234"
            << cipher10;
    QTest::newRow("16 char string (pwd: 0123456789)")
            << "V72Y/mhDjHuahrwo24olMLWz3KVIb8sbiO3KwpcJmPw="
            << "0123456789012345"
            << cipher10;
    QTest::newRow("17 char string (pwd: 0123456789)")
            << "F/Hu2ajWHBp9vpt+9Jb1Bjg/QfwD5Vvqpz/HeBMPZ1s="
            << "lorem ipsum dolor"
            << cipher10;

    QTest::newRow("Zero length string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "Af5kxa4xk7Zg6/ussZpHoQ=="
            << ""
            << cipherLongPassword;
    QTest::newRow("15 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "jJPklJTCC15wFuQP7RLQtg=="
            << "012345678901234"
            << cipherLongPassword;
    QTest::newRow("16 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "xu4SjRcX3LtNmM2U03x9hMT8zvKYit3ahcqJeEfAUcU="
            << "0123456789012345"
            << cipherLongPassword;
    QTest::newRow("17 char string (pwd: Lorem ipsum dolor sit amet, consectetur adipiscing elit)")
            << "vQWfizjcInX1u6BBTvtTaRsnZaOvSmwi/3pcv3t5EHs="
            << "lorem ipsum dolor"
            << cipherLongPassword;
}

void
TestCipher::decrypt(void)
{
    QFETCH(QString, encryptedString);
    QFETCH(QString, decryptedString);
    QFETCH(Cipher, cipherEngine);

    QCOMPARE(cipherEngine.decrypt(encryptedString), decryptedString);
}



void
TestCipher::encryptAndDecrypt_data(void)
{
    QTest::addColumn<QString>("stringToEncrypt");
    QTest::addColumn<Cipher>("cipherEngine");

    Cipher cipherGUEST;
    cipherGUEST.setPassword("GUEST");

    QTest::newRow("Zero length string (pwd: GUEST)") << "" << cipherGUEST;
    QTest::newRow("15 char string (pwd: GUEST)") << "012345678901234" << cipherGUEST;
    QTest::newRow("16 char string (pwd: GUEST)") << "0123456789012345" << cipherGUEST;
    QTest::newRow("17 char string (pwd: GUEST)") << "lorem ipsum dolor" << cipherGUEST;
}

void
TestCipher::encryptAndDecrypt(void)
{
    QFETCH(QString, stringToEncrypt);
    QFETCH(Cipher, cipherEngine);

    QCOMPARE(cipherEngine.decrypt(cipherEngine.encrypt(stringToEncrypt)), stringToEncrypt);
}
