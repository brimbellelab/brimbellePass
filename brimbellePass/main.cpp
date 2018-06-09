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

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);
    qApp->setWindowIcon(QIcon(":icons/brimbellePass.icns"));

    MainWindow w;
    w.show();

    return a.exec();
}
