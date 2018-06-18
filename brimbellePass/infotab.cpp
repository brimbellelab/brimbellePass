// InfoTab.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "infotab.h"

#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

InfoTab::InfoTab(QWidget *parent) : QWidget(parent)
{
    // Description.
    QLabel* description = new QLabel("BrimbellePass, a free, split-database password manager.", this);

    btnHelp = new QPushButton("Help");
    connect(btnHelp, SIGNAL(clicked()), this, SLOT(openHelp()));

    // Version.
    QLabel* version = new QLabel(QString("Version %1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH),
                                this);

    // Copyright.
    QLabel* copyright = new QLabel("Copyright (C) 2018, by Landry COLLET for BrimbelleLab.", this);

    // License.
    QLabel* license = new QLabel("Released under the GNU General Public License v3, see",
                                 this);
    license->setWordWrap(true);

    QLabel* licenseLink = new QLabel(this);
    licenseLink->setOpenExternalLinks(true);
    licenseLink->setText("<a href=\"https://www.gnu.org/licenses\">www.gnu.org/licenses</a>");

    // Contact.
    QLabel* contactPre = new QLabel("More on:", this);
    QLabel* contact = new QLabel(this);
    contact->setOpenExternalLinks(true);
    contact->setWordWrap(true);
    contact->setText("<a href=\"http://www.github.com/brimbellelab/brimbellepass\">www.github.com/brimbellelab/brimbellepass</a>");

    // Buy beer
    QLabel* buyBeer = new QLabel(this);
    buyBeer->setOpenExternalLinks(true);
    buyBeer->setText("<a href=\"https://www.paypal.me/LandryCOLLET\">Buy me a beer!</a>");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(description);
    layout->addWidget(btnHelp);
    layout->addWidget(version);
    layout->addWidget(copyright);
    layout->addWidget(license);
    layout->addWidget(licenseLink);
    layout->addWidget(contactPre);
    layout->addWidget(contact);
    layout->addWidget(buyBeer);
    layout->addSpacing(400);
    this->setLayout(layout);
}


void
InfoTab::openHelp(void)
{
    QMessageBox::warning(this,
                         "Oopsie",
                         "Unfortunately the help has not been written yet, but feel free to contribute!");
}
