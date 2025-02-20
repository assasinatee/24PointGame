#ifndef POKERS_H
#define POKERS_H

#include <QWidget>
#include <challenge.h>
#include <QRandomGenerator>
#include <QVector>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStack>
#include <QString>

namespace Ui {
class pokers;
}

class pokers : public QWidget
{
    Q_OBJECT

public:
    explicit pokers(challenge *c,int round = 1,bool time = 0,QWidget *parent = nullptr);
    ~pokers();
    void setPictures();
    void setAnimations();
    void iniPokers();
    void iniLcd();
    void iniLabels();
    void iniButtons();
    void setInvisible();
    void setButtonOpacityAnimation(QPushButton* button,QPropertyAnimation *m_opacity_animation);
    void setLabelOpacityAnimation(QLabel* label,QPropertyAnimation *m_opacity_animation);
    void resetLabelOpacityAnimation(QLabel* label,QPropertyAnimation *m_opacity_animation);
    void newRound();
    void message();
    void startTimer(int x);
    void newPokers();

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap pixmap("../images/background2.jpg");
        pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pixmap);
    }

private slots:
    void updateTime();

    void on_firstButton_clicked();

    void on_secondButton_clicked();

    void on_thirdButton_clicked();

    void on_fourthButton_clicked();

    void on_addButton_clicked();

    void on_subButton_clicked();

    void on_plusButton_clicked();

    void on_divButton_clicked();

    void on_refreshButton_clicked();

    void on_retButton_clicked();

    void on_answerButton_clicked();

private:
    Ui::pokers *ui;
    challenge *cha;
    int *nums;
    int *resNums;
    QVector<QVector<QString>> poker;
    QPushButton **buttons;
    QPushButton **symbols;
    QLabel** labels;
    QTimer *timer;
    int m_secCnt = 0;
    int m_minCnt = 0;
    bool isStart;
    bool isPressed[10];
    QStack<float> temps;
    int lastPressed = -1;
    int lastChar = -1;
    float* cur;
    int count = 4;
    int roundNum = 1;
    bool haveTimer = 0;
    QString answer;
};

#endif // POKERS_H
