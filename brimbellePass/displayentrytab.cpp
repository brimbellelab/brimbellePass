#include "displayentrytab.h"

#include <QVBoxLayout>

DisplayEntryTab::DisplayEntryTab(QWidget *parent) : QWidget(parent)
{
    comboBoxAccountsList = new QComboBox(this);
    // For now, just some dummy content in the combobox.
    comboBoxAccountsList->addItem("Amazon.com");
    comboBoxAccountsList->addItem("Bank.com");
    comboBoxAccountsList->addItem("Banned.com");
    comboBoxAccountsList->addItem("IRS");

    displayEntryContent = new DisplayEntryContent(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(comboBoxAccountsList);
    verticalLayout->addWidget(displayEntryContent);

    this->setLayout(verticalLayout);
}
