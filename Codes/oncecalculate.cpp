#include "oncecalculate.h"
#include "ui_oncecalculate.h"
#include "result.h"

onceCalculate::onceCalculate(Widget*mainWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::onceCalculate)
{
    ui->setupUi(this);
    w = mainWidget;
    num = 0;
    buttonList.append(ui->firstButton);
    buttonList.append(ui->secondButton);
    buttonList.append(ui->thirdButton);
    buttonList.append(ui->fourthButton);
    m_opacity_animations = new QPropertyAnimation*[15];
    for(int i = 0;i <= 13;i++){
        m_opacity_animations[i] = new QPropertyAnimation(this);
    }
}

onceCalculate::~onceCalculate()
{
    for(int i = 0;i < 13;i++){
        delete m_opacity_animations[i];
    }
    delete m_opacity_animations;
    delete ui;
}

bool d24(double a[], QString exp[], int n) {
    if (n == 1) {
        if (fabs(a[0] - 24) < 0.00000001) {
            qDebug() << "Expression: " << exp[0] << endl;
            return true;
        }
        return false;
    }
    else {
        bool f = false;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                double ai = a[i], aj = a[j];
                QString ei = exp[i], ej = exp[j];

                // Addition
                a[i] = ai + aj;
                exp[i] = "(" + ei + "+" + ej + ")";
                a[j] = a[n - 1];
                exp[j] = exp[n - 1];
                f = d24(a, exp, n - 1);
                if (f) return true;

                // Subtraction (ai - aj)
                a[i] = ai - aj;
                exp[i] = "(" + ei + "-" + ej + ")";
                a[j] = a[n - 1];
                exp[j] = exp[n - 1];
                f = d24(a, exp, n - 1);
                if (f) return true;

                // Subtraction (aj - ai)
                a[i] = aj - ai;
                exp[i] = "(" + ej + "-" + ei + ")";
                a[j] = a[n - 1];
                exp[j] = exp[n - 1];
                f = d24(a, exp, n - 1);
                if (f) return true;

                // Multiplication
                a[i] = ai * aj;
                exp[i] = "(" + ei + "*" + ej + ")";
                a[j] = a[n - 1];
                exp[j] = exp[n - 1];
                f = d24(a, exp, n - 1);
                if (f) return true;

                // Division (ai / aj)
                if (aj != 0) {
                    a[i] = ai / aj;
                    exp[i] = "(" + ei + "/" + ej + ")";
                    a[j] = a[n - 1];
                    exp[j] = exp[n - 1];
                    f = d24(a, exp, n - 1);
                    if (f) return true;
                }

                // Division (aj / ai)
                if (ai != 0) {
                    a[i] = aj / ai;
                    exp[i] = "(" + ej + "/" + ei + ")";
                    a[j] = a[n - 1];
                    exp[j] = exp[n - 1];
                    f = d24(a, exp, n - 1);
                    if (f) return true;
                }

                // Restore original values
                a[i] = ai;
                a[j] = aj;
                exp[i] = ei;
                exp[j] = ej;
            }
        }
        return false;
    }
}

void onceCalculate::DisableAllButtonExcept(QWidget *parentWidget, QPushButton *exceptionButton){
    for (auto *child : parentWidget->findChildren<QWidget *>()) {
            // 尝试将子控件转换为QPushButton
            QPushButton *button = qobject_cast<QPushButton *>(child);
            // 如果转换成功，并且该按钮不是我们要排除的按钮
            if (button && button != exceptionButton) {
                // 禁用该按钮
                button->setEnabled(false);
            }
        }
}

void onceCalculate::EnableAllButton(QWidget *parentWidget){
    for (auto *child : parentWidget->findChildren<QWidget *>()) {
            // 尝试将子控件转换为QPushButton
            QPushButton *button = qobject_cast<QPushButton *>(child);
            // 如果转换成功，启用该按钮
            if (button) {
                button->setEnabled(true);
            }
        }
}

void onceCalculate::setButtonOpacityAnimation(QPushButton* button,int i)
{
    // 1. 检查按钮是否已经有不透明度效果，并删除它（如果存在）
    QGraphicsOpacityEffect* opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(button->graphicsEffect());
    if (!opacityEffect) {
        opacityEffect = new QGraphicsOpacityEffect;
        button->setGraphicsEffect(opacityEffect);
    }
    // 假设 m_opacity_animation 已经在类的某个地方被定义和初始化
    // 3. 应用动画属性到不透明度效果
    m_opacity_animations[i]->setTargetObject(opacityEffect);

    // 4. 设置动画属性名
    m_opacity_animations[i]->setPropertyName("opacity");

    // 5. 设置动画的起始和结束值
    m_opacity_animations[i]->setStartValue(0.0);
    m_opacity_animations[i]->setEndValue(1.0);

    // 6. 设置动画的持续时间
    m_opacity_animations[i]->setDuration(300);

    // 7. 设置动画的缓和曲线
    m_opacity_animations[i]->setEasingCurve(QEasingCurve::Linear);

    // 8. 设置动画的播放周期（1 表示播放一次）
    m_opacity_animations[i]->setLoopCount(1);

    m_opacity_animations[i]->start();
}


void onceCalculate::on_retButton_clicked()
{
    w->show();
    delete this;
}

void onceCalculate::on_oneButton_clicked()
{
    if(num<4){
        q.enqueue(1);
        buttonList[num]->setText("1");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],1);
        num++;
    }
}

void onceCalculate::on_twoButton_clicked()
{
    if(num<4){
        q.enqueue(2);
        buttonList[num]->setText("2");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],2);
        num++;
    }
}

void onceCalculate::on_threeButton_clicked()
{
    if(num<4){
        q.enqueue(3);
        buttonList[num]->setText("3");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],3);
        num++;
    }
}

void onceCalculate::on_fourButton_clicked()
{
    if(num<4){
        q.enqueue(4);
        buttonList[num]->setText("4");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],4);
        num++;
    }
}

void onceCalculate::on_fiveButton_clicked()
{
    if(num<4){
        q.enqueue(5);
        buttonList[num]->setText("5");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],5);
        num++;
    }
}

void onceCalculate::on_sixButton_clicked()
{
    if(num<4){
        q.enqueue(6);
        buttonList[num]->setText("6");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],6);
        num++;
    }
}

void onceCalculate::on_sevenButton_clicked()
{
    if(num<4){
        q.enqueue(7);
        buttonList[num]->setText("7");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],7);
        num++;
    }
}

void onceCalculate::on_eightButton_clicked()
{
    if(num<4){
        q.enqueue(8);
        buttonList[num]->setText("8");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],8);
        num++;
    }
}

void onceCalculate::on_nineButton_clicked()
{
    if(num<4){
        q.enqueue(9);
        buttonList[num]->setText("9");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],9);
        num++;
    }
}

void onceCalculate::on_tenButton_clicked()
{
    if(num<4){
        q.enqueue(10);
        buttonList[num]->setText("10");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],10);
        num++;
    }
}

void onceCalculate::on_JButton_clicked()
{
    if(num<4){
        q.enqueue(11);
        buttonList[num]->setText("J");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],11);
        num++;
    }
}

void onceCalculate::on_QButton_clicked()
{
    if(num<4){
        q.enqueue(12);
        buttonList[num]->setText("Q");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],12);
        num++;
    }
}

void onceCalculate::on_KButton_clicked()
{
    if(num<4){
        q.enqueue(13);
        buttonList[num]->setText("K");
        buttonList[num]->setStyleSheet("QPushButton{"
                                       "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                       "border-radius:37px;"
                                       "font-size: 40px; "
                                       "font-family: Arial;"
                                       "}");
        setButtonOpacityAnimation(buttonList[num],13);
        num++;
    }
}

void onceCalculate::on_backButton_clicked()
{
    if(num>0){
        buttonList[num-1]->setText("");
        buttonList[num-1]->setStyleSheet("QPushButton{"
                                       "border-radius:37px;"
                                       "}");
        q.dequeue();
        num--;
    }
}


void onceCalculate::on_clearButton_clicked()
{
    for(int i = num-1;i >= 0;i--){
        buttonList[i]->setText("");
        buttonList[i]->setStyleSheet("QPushButton{"
                                       "border-radius:37px;"
                                       "}");
        q.dequeue();
        num--;
    }
}

void onceCalculate::on_calButton_clicked()
{
    if(num!=4){
        QMessageBox::critical(this, "温馨提示", "请选择四个数字");
        return;
    }
    double ini[4];
    QString strs[4];
    for(int i = 0;i < 4;i++){
        buttonList[i]->setText("");
        buttonList[i]->setStyleSheet("QPushButton{"
                                       "border-radius:37px;"
                                       "}");
        int x = q.dequeue();
        num--;
        ini[i]=(double)x;
        strs[i]=QString::number(x);
    }
    if(d24(ini,strs,4)){
        qDebug() << "Yes" << endl;
        qDebug() << strs[0] << endl;
        result* r=new result(w,this);
        r->showHave(strs[0] + "=24");
        r->show();
        this->hide();
    }
    else{
        result* r=new result(w,this);
        r->showNotHave();
        r->show();
        this->hide();
    }
}
