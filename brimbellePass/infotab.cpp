// InfoTab.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "infotab.h"

#include <QMessageBox>
#include <QVBoxLayout>

InfoTab::InfoTab(QWidget *parent) : QWidget(parent)
{
    // Description
    QLabel* description = new QLabel("BrimbellePass, a free, split-database password manager.", this);

    btnHelp = new QPushButton("Help");
    connect(btnHelp, SIGNAL(clicked()), this, SLOT(openHelp()));

    // Version
    QLabel* version = new QLabel("Version 0.0.1", this); // TODO Have a dedicated class for version control?
    // TODO Add a button to check for update.

    // Copyright
    QLabel* copyright = new QLabel("Copyright (C) 2018, by Landry COLLET for BrimbelleLab.", this);

    // License
    QLabel* license = new QLabel("Released under the GNU General Public License v3, see https://www.gnu.org/licenses",
                                 this);
    license->setWordWrap(true);

    // Contact
    QLabel* contact = new QLabel("More on\nhttp://www.github.com/brimbellelab/brimbellepass", this);
    contact->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(description);
    layout->addWidget(btnHelp);
    layout->addWidget(version);
    layout->addWidget(copyright);
    layout->addWidget(license);
    layout->addWidget(contact);
    layout->addSpacing(300);
    this->setLayout(layout);
}


void
InfoTab::openHelp(void)
{
    QMessageBox::warning(this,
                         "Oopsie",
                         "Unfortunately the help has not been written yet, but feel free to contribute!");
}
