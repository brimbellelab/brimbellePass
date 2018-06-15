// DialogAddSafetyQA.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "dialogaddsafetyqa.h"

#include <QMessageBox>
#include <QSizePolicy>
#include <QVBoxLayout>


DialogAddSafetyQA::DialogAddSafetyQA(QWidget *parent) : QDialog(parent)
{
    QLabel* newQuestionLabel = new QLabel("New safety question");
    newQuestionField = new QLineEdit("");
    QLabel* newAnswerLabel = new QLabel("New safety answer");
    newAnswerField = new QLineEdit("");
    newAnswerField->setEchoMode(QLineEdit::Password);
    newAnswerField->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    confirmNewAnswerLabel = new QLabel("Retype answer");
    confirmAnswerField = new QLineEdit("");
    confirmAnswerField->setEchoMode(QLineEdit::Password);
    confirmAnswerField->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    showAnswer = new QCheckBox("Show answer");
    btnOk = new QPushButton("Ok");

    QObject::connect(showAnswer, SIGNAL(toggled(bool)), this, SLOT(showAnswerText(bool)));
    QObject::connect(btnOk, SIGNAL(clicked()), this, SLOT(testAndReturn()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(newQuestionLabel);
    layout->addWidget(newQuestionField);
    layout->addWidget(newAnswerLabel);
    layout->addWidget(newAnswerField);
    layout->addWidget(confirmNewAnswerLabel);
    layout->addWidget(confirmAnswerField);
    layout->addWidget(showAnswer);
    layout->addWidget(btnOk);

    // Avoid rearranging the layout when masking the confirm answer widgets.
    QSizePolicy retainSizeConfirmAnswerField = confirmAnswerField->sizePolicy();
    retainSizeConfirmAnswerField.setRetainSizeWhenHidden(true);
    confirmAnswerField->setSizePolicy(retainSizeConfirmAnswerField);

    QSizePolicy retainSizeConfirmAnswerLabel = confirmNewAnswerLabel->sizePolicy();
    retainSizeConfirmAnswerLabel.setRetainSizeWhenHidden(true);
    confirmNewAnswerLabel->setSizePolicy(retainSizeConfirmAnswerLabel);

    this->setLayout(layout);
}



void
DialogAddSafetyQA::showAnswerText(bool show)
{
    if (show && (newAnswerField->echoMode() == QLineEdit::Password))
    {
        newAnswerField->setEchoMode(QLineEdit::Normal);
        confirmNewAnswerLabel->setVisible(false);
        confirmAnswerField->setVisible(false);
    }
    else if (!show && newAnswerField->echoMode() != QLineEdit::Password)
    {
        newAnswerField->setEchoMode(QLineEdit::Password);
        confirmNewAnswerLabel->setVisible(true);
        confirmAnswerField->setVisible(true);
    }
}



void
DialogAddSafetyQA::testAndReturn(void)
{
    // Start by checking that the 2 fields are the same when the showAnswer is not checked.
    if (showAnswer->checkState() != Qt::CheckState::Checked)
    {
        if (newAnswerField->text() != confirmAnswerField->text())
        {
            // Prepare data to have it ready
            QMessageBox::warning(this, "Answers mismatch", "The 2 answers are different");
            return;
        }
    }

    dataSafetyQA.first = newQuestionField->text();
    dataSafetyQA.second = newAnswerField->text();
    this->accept();
}



std::pair<QString, QString>
DialogAddSafetyQA::data(void)
{
    return dataSafetyQA;
}
