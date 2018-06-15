// safetyqawidget.h - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#ifndef SAFETYQAWIDGET_H
#define SAFETYQAWIDGET_H

#include "cipher.h"
#include "passwordentryline.h"

#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QVector>
#include <QWidget>

#include <vector>

class SafetyQAWidget : public QWidget
{
    Q_OBJECT
public:
    SafetyQAWidget(QWidget *parent, Cipher* cipher, const int margin = 0);
    virtual ~SafetyQAWidget() = default;
    /// Get the number of question / answer pairs.
    int count(void);
    const QString& getQuestionText(const int index);
    const QString& getAnswerCryptedText(const int index);
    void setData(std::vector<std::pair<std::string, std::string> > data);

public slots:
    void clear(void);

private slots:
    void addSafetyQA(void);

    // Update the content of the safety answer field.
    // @param[in] index Index of the safety answer to be loaded.
    void updateSafetyAnswerField(const int index);

    /// Called when a change is made on the answer field, or maybe when the qcombobox is opened?
    void saveDataSafetyAnswer(void);

private:
    Cipher* cipherEngine; // Needed to decrypt safety answers.
    QGroupBox* gbSafetyQA;
    QComboBox* comboBoxSafetyQuestion;
    QPushButton* btnNewSafetyQA;
    PasswordEntryLine* safetyAnswer;
    QVector<std::pair<QString, QString> > dataSafetyQA; // Answers are stored crypted.
};

#endif // SAFETYQAWIDGET_H
