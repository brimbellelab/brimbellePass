// BrimbellePass, a split-database password manager.

// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.

// BrimbellePass is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or any
// later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.

#include "mainwindow.h"

#include "brimbellepasserror.h"

#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
    qApp->setWindowIcon(QIcon(":icons/brimbellePass.icns"));

    try
    {
        MainWindow w;
        w.show();
        std::cout << "Starting...\n" << std::endl;
        return a.exec();
    }
    catch (BrimbellePassError err)
    {
        std::cout << "BrimbellePass failed to start: ";
        switch (err)
        {
            case BrimbellePassError::noConfigFile:
                std::cout << "No configuration file!" << std::endl;
            break;
            default:
                std::cout << "Unhandled error code: " << static_cast<int>(err) << std::endl;
                break;
        }
    }
    return -1;
}
