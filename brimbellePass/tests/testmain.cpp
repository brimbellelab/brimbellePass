// testmain.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include <QtTest/QtTest>

#include "testaccountsbook.h"
#include "testcipher.h"

int main(int argc, char *argv[])
{
    int status = 0;

    status |= QTest::qExec(new TestCipher, argc, argv);
    status |= QTest::qExec(new TestAccountsBook, argc, argv);

    return status;
}
