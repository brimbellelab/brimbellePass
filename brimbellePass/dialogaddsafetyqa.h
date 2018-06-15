#ifndef DIALOGADDSAFETYQA_H
#define DIALOGADDSAFETYQA_H

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class DialogAddSafetyQA : public QDialog
{
    Q_OBJECT
public:
    explicit DialogAddSafetyQA(QWidget *parent = 0);

    std::pair<QString, QString> data(void);
signals:

public slots:

private slots:
    void showAnswerText(bool show);
    void testAndReturn(void);

private:
    QLineEdit* newQuestionField;
    QLineEdit* newAnswerField;
    QLabel* confirmNewAnswerLabel;
    QLineEdit* confirmAnswerField;
    QCheckBox* showAnswer;
    QPushButton* btnOk;
    std::pair<QString, QString> dataSafetyQA;
};

#endif // DIALOGADDSAFETYQA_H
