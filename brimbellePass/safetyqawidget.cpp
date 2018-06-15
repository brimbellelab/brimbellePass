// safetyqawidget.c - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "safetyqawidget.h"

#include "dialogaddsafetyqa.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QVBoxLayout>

#include <iostream>

using namespace std;

SafetyQAWidget::SafetyQAWidget(QWidget *parent, Cipher* cipher, const int margin) : QWidget(parent)
{
    cipherEngine = cipher;

    gbSafetyQA = new QGroupBox("Safety questions");
    comboBoxSafetyQuestion = new QComboBox();
    if (comboBoxSafetyQuestion->count() > 0)
    {
        updateSafetyAnswerField(0); // Always point at the first item on creation.
    }

    btnNewSafetyQA = new QPushButton("+");
    btnNewSafetyQA->setMaximumSize(20, 20);
    QObject::connect(btnNewSafetyQA, SIGNAL(clicked()), this, SLOT(addSafetyQA()));

    QHBoxLayout* layoutSafetyQuestions = new QHBoxLayout;
    if (margin != 0)
    {
        layoutSafetyQuestions->setMargin(margin);
    }
    layoutSafetyQuestions->addWidget(comboBoxSafetyQuestion);
    layoutSafetyQuestions->addWidget(btnNewSafetyQA);

    safetyAnswer = new PasswordEntryLine("");
    QObject::connect(safetyAnswer, SIGNAL(passwordChanged()), this, SLOT(saveDataSafetyAnswer()));

    QVBoxLayout *layoutSafetyQA = new QVBoxLayout;
    layoutSafetyQA->addLayout(layoutSafetyQuestions);
    layoutSafetyQA->addWidget(safetyAnswer);
    if (margin != 0)
    {
        layoutSafetyQA->setMargin(margin);
    }
    gbSafetyQA->setLayout(layoutSafetyQA);
    QObject::connect(comboBoxSafetyQuestion, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(updateSafetyAnswerField(const int)));

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(gbSafetyQA);
    mainLayout->setMargin(1);
    this->setLayout(mainLayout);
}



int
SafetyQAWidget::count(void)
{
    return dataSafetyQA.count();
}



const QString&
SafetyQAWidget::getQuestionText(const int index)
{
    if (index >= comboBoxSafetyQuestion->count())
    {
        throw QString("Attempt to access an invalid slot in comboBoxSafetyQuestion");
    }
    return dataSafetyQA[index].first;
}



const QString&
SafetyQAWidget::getAnswerCryptedText(const int index)
{
    if (index >= comboBoxSafetyQuestion->count())
    {
        throw QString("Attempt to access an invalid slot in comboBoxSafetyQuestion");
    }
    return dataSafetyQA[index].second;
}



void
SafetyQAWidget::setData(vector<pair<string, string> > data)
{
    // Erase previous data.
    dataSafetyQA.clear();

    // Attribute new data.
    dataSafetyQA.resize(data.size());
    for (size_t index = 0; index < data.size(); ++index)
    {
        dataSafetyQA[index].first = QString::fromStdString(data[index].first);
        dataSafetyQA[index].second = QString::fromStdString(data[index].second);
    }

    for (int index = 0; index < dataSafetyQA.size(); ++index)
    {
        comboBoxSafetyQuestion->addItem(dataSafetyQA[index].first);
    }

    updateSafetyAnswerField(0);
}



void
SafetyQAWidget::clear(void)
{
    // Erase the content of the widgets.
    // Clean "safety questions" field.
    comboBoxSafetyQuestion->blockSignals(true);
    safetyAnswer->blockSignals(true);
    comboBoxSafetyQuestion->clear();
    safetyAnswer->setText("");
    dataSafetyQA.clear();
    comboBoxSafetyQuestion->blockSignals(false);
    safetyAnswer->blockSignals(false);
}



void
SafetyQAWidget::addSafetyQA(void)
{
    DialogAddSafetyQA* dialog = new DialogAddSafetyQA(this);
    if (dialog->exec())
    {
        // Append the result to the existing data QVector.
        pair<QString, QString> newSafetyQA = dialog->data();
        newSafetyQA.second = cipherEngine->encrypt(newSafetyQA.second);
        dataSafetyQA.append(newSafetyQA);

        // Select it in the combo box.
        comboBoxSafetyQuestion->addItem(dataSafetyQA.constLast().first);
        comboBoxSafetyQuestion->setCurrentIndex(comboBoxSafetyQuestion->count() - 1);
    }
    delete dialog;
}




void
SafetyQAWidget::updateSafetyAnswerField(const int index)
{
    // As defined in the Qt doc, QComboBox::currentIndexChanged signal can send -1 if the comboBox becomes empty or if
    // index is reset.
    constexpr int resetOrEmptyQComboBoxIndexChangedCode = -1;
    if ((index == resetOrEmptyQComboBoxIndexChangedCode)
        || (index >= dataSafetyQA.count()))
    {
        safetyAnswer->setText("");
        return;
    }
    try
    {
        safetyAnswer->setText(cipherEngine->decrypt(dataSafetyQA[index].second));
    }
    catch (runtime_error re)
    {
        // No need to display a message box asking for the password again.
        cout << re.what() << endl;
    }
}



void
SafetyQAWidget::saveDataSafetyAnswer(void)
{
    int currentQuestionIndex = comboBoxSafetyQuestion->currentIndex();

    if (currentQuestionIndex < 0)
    {
        cout << "Invalid current question index" << endl;
        return;
    }

    // If the password field is empty, this question should be deleted.
    // However, for now, it will be deleted only when clicking the button "Save account", so proceed as usual.
//    if (safetyAnswer->text().isEmpty())
//    {
//        cout << "delete the safety question" << endl;
//        // TODO
//        return;
//    }

    try
    {
        QString encryptedAnswer = cipherEngine->encrypt(safetyAnswer->text());
        dataSafetyQA[currentQuestionIndex].second = encryptedAnswer;
    }
    catch (runtime_error err)
    {
        // Error while encrypting the new secret answer.
        cout << err.what() << endl;
    }
}
