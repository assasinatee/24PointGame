#ifndef ONCECALCULATE_H
#define ONCECALCULATE_H

#include <QWidget>
#include <widget.h>
#include <QQueue>
#include <QList>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QMessageBox>
#include <cmath>
#include <QString>
#include <QDebug>
#include <QKeyEvent>
#include "ui_oncecalculate.h"

namespace Ui {
class onceCalculate;
}

bool d24(double a[], QString exp[], int n);

class onceCalculate : public QWidget
{
    Q_OBJECT

public:
    explicit onceCalculate(Widget*mainWidget, QWidget *parent = nullptr);
    ~onceCalculate();
    void DisableAllButtonExcept(QWidget *parentWidget, QPushButton *exceptionButton);
    void EnableAllButton(QWidget *parentWidget);
    void setButtonOpacityAnimation(QPushButton* button, int i);


protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap pixmap("../images/background1.jpg");
        pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pixmap);
    }

    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_1) {
           ui->oneButton->setDown(true);
         }
        else if(event->key() == Qt::Key_2){
           ui->twoButton->setDown(true);
        }
        else if(event->key() == Qt::Key_3){
           ui->threeButton->setDown(true);
        }
        else if(event->key() == Qt::Key_4){
           ui->fourButton->setDown(true);
        }
        else if(event->key() == Qt::Key_5){
           ui->fiveButton->setDown(true);
        }
        else if(event->key() == Qt::Key_6){
           ui->sixButton->setDown(true);
        }
        else if(event->key() == Qt::Key_7){
           ui->sevenButton->setDown(true);
        }
        else if(event->key() == Qt::Key_8){
           ui->eightButton->setDown(true);
        }
        else if(event->key() == Qt::Key_9){
           ui->nineButton->setDown(true);
        }
        else if(event->key() == Qt::Key_0){
           ui->tenButton->setDown(true);
        }
        else if(event->key() == Qt::Key_J){
           ui->JButton->setDown(true);
        }
        else if(event->key() == Qt::Key_Q){
           ui->QButton->setDown(true);
        }
        else if(event->key() == Qt::Key_K){
           ui->KButton->setDown(true);
        }
        else if(event->key() == Qt::Key_Backspace){
           ui->backButton->setDown(true);
        }
        else if(event->key() == Qt::Key_Enter){
           ui->calButton->setDown(true);
        }
        else {
           QWidget::keyPressEvent(event); // 调用基类的实现以处理其他按键
        }
   }

    void keyReleaseEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_1) { // 假设使用空格键来模拟按钮抬起
            ui->oneButton->setDown(false); // 设置按钮为抬起状态
            on_oneButton_clicked();
        }
        else if(event->key() == Qt::Key_2){
           ui->twoButton->setDown(false); // 设置按钮为抬起状态
           on_twoButton_clicked();
        }
        else if(event->key() == Qt::Key_3){
           ui->threeButton->setDown(false); // 设置按钮为抬起状态
           on_threeButton_clicked();
        }
        else if(event->key() == Qt::Key_4){
           ui->fourButton->setDown(false); // 设置按钮为抬起状态
           on_fourButton_clicked();
        }
        else if(event->key() == Qt::Key_5){
           ui->fiveButton->setDown(false); // 设置按钮为抬起状态
           on_fiveButton_clicked();
        }
        else if(event->key() == Qt::Key_6){
           ui->sixButton->setDown(false); // 设置按钮为抬起状态
           on_sixButton_clicked();
        }
        else if(event->key() == Qt::Key_7){
           ui->sevenButton->setDown(false); // 设置按钮为抬起状态
           on_sevenButton_clicked();
        }
        else if(event->key() == Qt::Key_8){
           ui->eightButton->setDown(false); // 设置按钮为抬起状态
           on_eightButton_clicked();
        }
        else if(event->key() == Qt::Key_9){
           ui->nineButton->setDown(false); // 设置按钮为抬起状态
           on_nineButton_clicked();
        }
        else if(event->key() == Qt::Key_0){
            ui->tenButton->setDown(false); // 设置按钮为抬起状态
            on_tenButton_clicked();
        }
        else if(event->key() == Qt::Key_J){
           ui->JButton->setDown(false); // 设置按钮为抬起状态
           on_JButton_clicked();
        }
        else if(event->key() == Qt::Key_Q){
           ui->QButton->setDown(false); // 设置按钮为抬起状态
           on_QButton_clicked();
        }
        else if(event->key() == Qt::Key_K){
           ui->KButton->setDown(false); // 设置按钮为抬起状态
           on_KButton_clicked();
        }
        else if(event->key() == Qt::Key_Backspace){
           ui->backButton->setDown(false); // 设置按钮为抬起状态
           on_backButton_clicked();
        }
        else if(event->key() == Qt::Key_Enter){
           ui->calButton->setDown(false); // 设置按钮为抬起状态
           on_calButton_clicked();
        }
        else {
            QWidget::keyReleaseEvent(event); // 调用基类的实现以处理其他按键
        }
    }

private slots:
    void on_retButton_clicked();

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_tenButton_clicked();

    void on_JButton_clicked();

    void on_QButton_clicked();

    void on_KButton_clicked();

    void on_backButton_clicked();

    void on_clearButton_clicked();

    void on_calButton_clicked();

private:
    Ui::onceCalculate *ui;
    Widget *w;
    QQueue<int> q;
    int num;
    QList<QPushButton*> buttonList;
    QPropertyAnimation **m_opacity_animations;
};

#endif // ONCECALCULATE_H
