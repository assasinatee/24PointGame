#include "pokers.h"
#include "ui_pokers.h"
#include "oncecalculate.h"
#include <QDebug>


pokers::pokers(challenge *c,int round,bool time,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pokers)
{
    ui->setupUi(this);
    cha = c;
    roundNum = round;
    haveTimer = time;
    nums = new int[15];
    resNums = new int[4];
    cur = new float[4];
    for(int i = 1;i < 14;i++){
        nums[i]=i;
    }
    for(int i = 0;i < 10;i++){
        isPressed[i]=0;
    }
    iniPokers();
    iniLabels();
    iniLcd();
    iniButtons();
    setInvisible();
    setPictures();
    setAnimations();
}

void pokers::setButtonOpacityAnimation(QPushButton* button,QPropertyAnimation *m_opacity_animation)
{
    // 1. 检查按钮是否已经有不透明度效果，并删除它（如果存在）
    QGraphicsOpacityEffect* opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(button->graphicsEffect());
    if (!opacityEffect) {
        opacityEffect = new QGraphicsOpacityEffect;
        button->setGraphicsEffect(opacityEffect);
    }
    // 假设 m_opacity_animation 已经在类的某个地方被定义和初始化
    // 3. 应用动画属性到不透明度效果
    m_opacity_animation->setTargetObject(opacityEffect);

    // 4. 设置动画属性名
    m_opacity_animation->setPropertyName("opacity");

    // 5. 设置动画的起始和结束值
    m_opacity_animation->setStartValue(0.0);
    m_opacity_animation->setEndValue(1.0);

    // 6. 设置动画的持续时间
    m_opacity_animation->setDuration(300);

    // 7. 设置动画的缓和曲线
    m_opacity_animation->setEasingCurve(QEasingCurve::Linear);

    // 8. 设置动画的播放周期（1 表示播放一次）
    m_opacity_animation->setLoopCount(1);
}

void pokers::setLabelOpacityAnimation(QLabel* label,QPropertyAnimation *m_opacity_animation)
{
    // 1. 检查按钮是否已经有不透明度效果，并删除它（如果存在）
    QGraphicsOpacityEffect* opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(label->graphicsEffect());
    if (!opacityEffect) {
        opacityEffect = new QGraphicsOpacityEffect;
        label->setGraphicsEffect(opacityEffect);
    }
    // 假设 m_opacity_animation 已经在类的某个地方被定义和初始化
    // 3. 应用动画属性到不透明度效果
    m_opacity_animation->setTargetObject(opacityEffect);

    // 4. 设置动画属性名
    m_opacity_animation->setPropertyName("opacity");

    // 5. 设置动画的起始和结束值
    m_opacity_animation->setStartValue(0.0);
    m_opacity_animation->setEndValue(1.0);

    // 6. 设置动画的持续时间
    m_opacity_animation->setDuration(300);

    // 7. 设置动画的缓和曲线
    m_opacity_animation->setEasingCurve(QEasingCurve::Linear);

    // 8. 设置动画的播放周期（1 表示播放一次）
    m_opacity_animation->setLoopCount(1);
}

void pokers::resetLabelOpacityAnimation(QLabel* label,QPropertyAnimation *m_opacity_animation)
{
    // 1. 检查按钮是否已经有不透明度效果，并删除它（如果存在）
    QGraphicsOpacityEffect* opacityEffect = qobject_cast<QGraphicsOpacityEffect*>(label->graphicsEffect());
    if (!opacityEffect) {
        opacityEffect = new QGraphicsOpacityEffect;
        label->setGraphicsEffect(opacityEffect);
    }
    // 假设 m_opacity_animation 已经在类的某个地方被定义和初始化
    // 3. 应用动画属性到不透明度效果
    m_opacity_animation->setTargetObject(opacityEffect);

    // 4. 设置动画属性名
    m_opacity_animation->setPropertyName("opacity");

    // 5. 设置动画的起始和结束值
    m_opacity_animation->setStartValue(1.0);
    m_opacity_animation->setEndValue(0.0);

    // 6. 设置动画的持续时间
    m_opacity_animation->setDuration(300);

    // 7. 设置动画的缓和曲线
    m_opacity_animation->setEasingCurve(QEasingCurve::Linear);

    // 8. 设置动画的播放周期（1 表示播放一次）
    m_opacity_animation->setLoopCount(1);
}

void pokers::iniPokers(){
    //初始化pokers
    QVector<QString> tmp;
    poker.append(tmp);
    for(int i = 1;i < 14;i++){
        QVector<QString> temp;
        QString t1 = "../images/pokerCards/fk" + QString::number(i) + ".jpg";
        QString t2 = "../images/pokerCards/hot" + QString::number(i) + ".jpg";
        QString t3 = "../images/pokerCards/ht" + QString::number(i) + ".jpg";
        QString t4 = "../images/pokerCards/mh" + QString::number(i) + ".jpg";
        temp.append(t1);
        temp.append(t2);
        temp.append(t3);
        temp.append(t4);
        poker.append(temp);
    }
}

void pokers::iniLcd(){
    timer = new QTimer;
    isStart = false;     //初始为还未计时
    m_secCnt = 10;
    m_minCnt = 0;
    ui->lcdNumber->setDigitCount(4);//显示位数
    ui->lcdNumber->setMode(QLCDNumber::Dec);//设置显示模式为十进制
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Outline);//设置显示外观Outline、Filled、Flat三种
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    ui->lcdNumber->setVisible(false);
}

void pokers::iniLabels(){
    //初始化labels
    labels = new QLabel*[4];
    labels[0] = ui->label1;
    labels[1] = ui->label2;
    labels[2] = ui->label3;
    labels[3] = ui->label4;
    ui->label_2->setText("第"+QString::number(roundNum)+"关");
    ui->label_3->setText("这一关你有"+QString::number((130-10*roundNum>=30)?(130-10*roundNum):30)+"秒的时间完成");
    for(int i = 0;i<4;i++){
        labels[i]->setVisible(false);
    }
}

void pokers::newPokers(){
    pokers *p = new pokers(cha,1,1);
    p->show();
    delete this;
}

void pokers::iniButtons(){
    buttons =new QPushButton*[5];
    buttons[1] = ui->firstButton;
    buttons[2] = ui->secondButton;
    buttons[3] = ui->thirdButton;
    buttons[4] = ui->fourthButton;
    symbols = new QPushButton*[5];
    symbols[1] = ui->addButton;
    symbols[2] = ui->subButton;
    symbols[3] = ui->plusButton;
    symbols[4] = ui->divButton;
}

void pokers::setInvisible(){
     ui->label->setVisible(false);
     ui->firstButton->setVisible(false);
     ui->secondButton->setVisible(false);
     ui->thirdButton->setVisible(false);
     ui->fourthButton->setVisible(false);
     ui->addButton->setVisible(false);
     ui->subButton->setVisible(false);
     ui->plusButton->setVisible(false);
     ui->divButton->setVisible(false);
     ui->refreshButton->setVisible(false);
     ui->answerButton->setVisible(false);
     if(!haveTimer){
         ui->label_3->setVisible(false);
     }
}

void pokers::updateTime(){
    if(m_secCnt >= 60){
        m_minCnt = m_secCnt/60;
        m_secCnt %= 60;
    }
    QString min = QString::number(m_minCnt);
    QString sec = QString::number(m_secCnt);
    if(min.length() == 1) min = "0" + min;
    if(sec.length() == 1) sec = "0" + sec;
    QString timeToShow = min + ":" + sec;
    ui->lcdNumber->display(timeToShow);

    if(m_minCnt == 0 && m_secCnt == 0) {
        timer->stop();
        m_secCnt = 0;
        m_minCnt = 0;
        isStart = false;
        QMessageBox msgBox;
        msgBox.setWindowTitle("失败提示");
        msgBox.setText("挑战失败");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setButtonText(QMessageBox::Save, "重新挑战");
        msgBox.setButtonText(QMessageBox::Cancel, "返回主菜单");
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
            newPokers();
            break;
          case QMessageBox::Cancel:
            cha->show();
            delete this;
            break;
          default:
              // should never be reached
            break;
        }
    }
    if(m_secCnt == 0) {
        m_secCnt = 60;
        m_minCnt--;
    }
    m_secCnt--;
}

void pokers::startTimer(int x = 0){
    //开始计时部分
    x = (130-10*roundNum>=30)?(130-10*roundNum):30;
    if(!isStart) //尚未开始 开始计时
    {
        timer->start(1000);
        m_secCnt = x;
        isStart = 1;
        if(m_secCnt >= 60){
            m_minCnt = m_secCnt/60;
            m_secCnt %= 60;
        }
        QString min = QString::number(m_minCnt);
        QString sec = QString::number(m_secCnt);
        if(min.length() == 1) min = "0" + min;
        if(sec.length() == 1) sec = "0" + sec;
        QString timeToShow = min + ":" + sec;
        ui->lcdNumber->display(timeToShow);
    }
    x--;
}

bool isFloatInteger(float value) {
    // 定义一个非常小的阈值（epsilon）
    const float epsilon = 0.001;
    // 检查小数部分是否接近于0
    return std::fabs(value - std::round(value)) < epsilon;
}

int *fourRandomNums(){
    int *numbers = new int[4];
    for(int i = 0;i < 4;i++){
        numbers[i] = QRandomGenerator::global()->bounded(1, 14);
    }
    return numbers;
}

int *fourRandomNumbers(){
    int *numbers = new int[4];
    for(int i = 0;i < 4;i++){
        numbers[i] = QRandomGenerator::global()->bounded(0,4);
    }
    return numbers;
}

void pokers::setPictures(){
    int *numbers = fourRandomNums();
    int *random = fourRandomNumbers();
    QString strs[4];
    double* a = new double[4];
    for(int i = 0;i < 4;i++){
        a[i] = numbers[i];
        strs[i]=QString::number(a[i]);
        cur[i] = a[i];
    }
    while(!d24(a,strs,4)){
        numbers = fourRandomNums();
        for(int i = 0;i < 4;i++){
            a[i] = numbers[i];
            strs[i]=QString::number(a[i]);
            cur[i] = a[i];
        }
    }
    answer = strs[0];
    resNums = numbers;
    ui->firstButton->setText(QString::number(numbers[0]));
    ui->secondButton->setText(QString::number(numbers[1]));
    ui->thirdButton->setText(QString::number(numbers[2]));
    ui->fourthButton->setText(QString::number(numbers[3]));
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < i;j++){
            if(numbers[i]==numbers[j]){
                while(random[i]==random[j]){
                    random[i] = QRandomGenerator::global()->bounded(0,4);
                }
            }
        }
        QString addr = poker[numbers[i]][random[i]];
        labels[i]->setScaledContents(true); // 启用内容缩放
        labels[i]->setPixmap(QPixmap(addr));
    }
}

void pokers::setAnimations(){
    QSequentialAnimationGroup *sequential = new QSequentialAnimationGroup(this);
    QParallelAnimationGroup *parallel1 = new QParallelAnimationGroup(this);
    QParallelAnimationGroup *parallel2 = new QParallelAnimationGroup(this);
    QParallelAnimationGroup *parallel0 = new QParallelAnimationGroup(this);

    QPropertyAnimation *labelAnimation0 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label_2,labelAnimation0);
    QPropertyAnimation *labelAnimation00 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label_3,labelAnimation00);
    QParallelAnimationGroup *parallel00 = new QParallelAnimationGroup(this);
    parallel00->addAnimation(labelAnimation0);
    parallel00->addAnimation(labelAnimation00);


    QPropertyAnimation *labelAnimation1 = new QPropertyAnimation(this);
    resetLabelOpacityAnimation(ui->label_2,labelAnimation1);
    QPropertyAnimation *labelAnimation11 = new QPropertyAnimation(this);
    resetLabelOpacityAnimation(ui->label_3,labelAnimation11);
    QParallelAnimationGroup *parallel11 = new QParallelAnimationGroup(this);
    parallel11->addAnimation(labelAnimation1);
    parallel11->addAnimation(labelAnimation11);
    connect(labelAnimation1, &QPropertyAnimation::finished,[this]() {
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
    });

    QPropertyAnimation *pokerAnimation1 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label1,pokerAnimation1);
    connect(pokerAnimation1, &QPropertyAnimation::valueChanged,[this]() {
        ui->label1->setVisible(true);
    });

    QPropertyAnimation *pokerAnimation2 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label2,pokerAnimation2);
    connect(pokerAnimation2, &QPropertyAnimation::valueChanged,[this]() {
        ui->label2->setVisible(true);
    });

    QPropertyAnimation *pokerAnimation3 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label3,pokerAnimation3);
    connect(pokerAnimation3, &QPropertyAnimation::valueChanged,[this]() {
        ui->label3->setVisible(true);
    });

    QPropertyAnimation *pokerAnimation4 = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label4,pokerAnimation4);
    connect(pokerAnimation4, &QPropertyAnimation::valueChanged,[this]() {
        ui->label4->setVisible(true);
    });

    parallel0->addAnimation(pokerAnimation1);
    parallel0->addAnimation(pokerAnimation2);
    parallel0->addAnimation(pokerAnimation3);
    parallel0->addAnimation(pokerAnimation4);

    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->label1, "pos");
    animation1->setDuration(300);
    animation1->setStartValue(ui->label1->pos());
    animation1->setEndValue(QPoint(10, 30));

    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->label2, "pos");
    animation2->setDuration(300);
    animation2->setStartValue(ui->label2->pos());
    animation2->setEndValue(QPoint(135, 30));

    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label3, "pos");
    animation3->setDuration(300);
    animation3->setStartValue(ui->label3->pos());
    animation3->setEndValue(QPoint(260, 30));

    QPropertyAnimation *animation4 = new QPropertyAnimation(ui->label4, "pos");
    animation4->setDuration(300);
    animation4->setStartValue(ui->label4->pos());
    animation4->setEndValue(QPoint(385, 30));

    QPropertyAnimation *labelAnimation = new QPropertyAnimation(this);
    setLabelOpacityAnimation(ui->label,labelAnimation);
    connect(labelAnimation, &QPropertyAnimation::valueChanged,[this]() {
        ui->label->setVisible(true);
    });

    QPropertyAnimation *animation5 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->firstButton,animation5);
    connect(animation5, &QPropertyAnimation::valueChanged,[this]() {
        ui->firstButton->setVisible(true);
    });

    QPropertyAnimation *animation6 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->secondButton,animation6);
    connect(animation6, &QPropertyAnimation::valueChanged,[this]() {
        ui->secondButton->setVisible(true);
    });

    QPropertyAnimation *animation7 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->thirdButton,animation7);
    connect(animation7, &QPropertyAnimation::valueChanged,[this]() {
        ui->thirdButton->setVisible(true);
    });

    QPropertyAnimation *animation8 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->fourthButton,animation8);
    connect(animation8, &QPropertyAnimation::valueChanged,[this]() {
        ui->fourthButton->setVisible(true);
    });

    QPropertyAnimation *animation9 = new QPropertyAnimation(ui->firstButton, "pos");
    animation9->setDuration(150);
    animation9->setStartValue(ui->firstButton->pos());
    animation9->setEndValue(QPoint(140, 40));

    QPropertyAnimation *animation10 = new QPropertyAnimation(ui->secondButton, "pos");
    animation10->setDuration(150);
    animation10->setStartValue(ui->secondButton->pos());
    animation10->setEndValue(QPoint(260, 40));

    QPropertyAnimation *animation11 = new QPropertyAnimation(ui->thirdButton, "pos");
    animation11->setDuration(150);
    animation11->setStartValue(ui->thirdButton->pos());
    animation11->setEndValue(QPoint(140, 160));

    QPropertyAnimation *animation12 = new QPropertyAnimation(ui->fourthButton, "pos");
    animation12->setDuration(150);
    animation12->setStartValue(ui->fourthButton->pos());
    animation12->setEndValue(QPoint(260, 160));

    connect(animation9, &QPropertyAnimation::valueChanged,[this]() {
        ui->label->setVisible(false);
        ui->label1->setVisible(false);
        ui->label2->setVisible(false);
        ui->label3->setVisible(false);
        ui->label4->setVisible(false);
    });

    QPropertyAnimation *animation13 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->addButton,animation13);
    connect(animation13, &QPropertyAnimation::valueChanged,[this]() {
        ui->addButton->setVisible(true);
    });

    QPropertyAnimation *animation14 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->subButton,animation14);
    connect(animation14, &QPropertyAnimation::valueChanged,[this]() {
        ui->subButton->setVisible(true);
    });

    QPropertyAnimation *animation15 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->plusButton,animation15);
    connect(animation15, &QPropertyAnimation::valueChanged,[this]() {
        ui->plusButton->setVisible(true);
    });

    QPropertyAnimation *animation16 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->divButton,animation16);
    connect(animation16, &QPropertyAnimation::valueChanged,[this]() {
        ui->divButton->setVisible(true);
    });

    QPropertyAnimation *animation17 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->refreshButton,animation17);
    connect(animation17, &QPropertyAnimation::valueChanged,[this]() {
        ui->refreshButton->setVisible(true);
    });

    QPropertyAnimation *animation18 = new QPropertyAnimation(this);
    setButtonOpacityAnimation(ui->answerButton,animation18);
    connect(animation18, &QPropertyAnimation::valueChanged,[this]() {       
        if(haveTimer){
            ui->lcdNumber->setVisible(true);
            ui->answerButton->setVisible(false);
            startTimer();
        }
        else{
            ui->answerButton->setVisible(true);
        }
    });

    parallel1->addAnimation(animation5);
    parallel1->addAnimation(animation6);
    parallel1->addAnimation(animation7);
    parallel1->addAnimation(animation8);

    parallel2->addAnimation(animation13);
    parallel2->addAnimation(animation14);
    parallel2->addAnimation(animation15);
    parallel2->addAnimation(animation16);
    parallel2->addAnimation(animation17);
    parallel2->addAnimation(animation18);

    sequential->addAnimation(parallel00);
    sequential->addPause(500);
    sequential->addAnimation(parallel11);
    sequential->addAnimation(parallel0);
    sequential->addPause(100);
    sequential->addAnimation(animation1);
    sequential->addPause(100);
    sequential->addAnimation(animation2);
    sequential->addPause(100);
    sequential->addAnimation(animation3);
    sequential->addPause(100);
    sequential->addAnimation(animation4);
    sequential->addPause(100);
    sequential->addAnimation(labelAnimation);
    sequential->addPause(100);
    sequential->addAnimation(parallel1);
    sequential->addPause(1000);
    sequential->addAnimation(animation9);
    sequential->addPause(100);
    sequential->addAnimation(animation10);
    sequential->addPause(100);
    sequential->addAnimation(animation11);
    sequential->addPause(100);
    sequential->addAnimation(animation12);
    sequential->addPause(100);
    sequential->addAnimation(parallel2);

    sequential->start();
}

pokers::~pokers()
{
    delete ui;
}

bool checkSymbol(int x){
    if(x=='+'||x=='-'||x=='*'||x=='/')return true;
    return false;
}

void pokers::newRound(){
    pokers *p;
    if(haveTimer){
        p = new pokers(cha,++roundNum,1);
    }
    else{
        p = new pokers(cha,++roundNum);
    }
    p->show();
    delete this;
}

void pokers::message(){
    timer->stop();
    QMessageBox msgBox;
    msgBox.setWindowTitle("成功啦！");
    msgBox.setText("恭喜你成功通过第"+QString::number(roundNum)+"关");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setButtonText(QMessageBox::Save, "下一关");
    msgBox.setButtonText(QMessageBox::Cancel, "返回主菜单");
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
        newRound();
        break;
      case QMessageBox::Cancel:
        cha->show();
        delete this;
        break;
      default:
          // should never be reached
        break;
    }
}

void pokers::on_firstButton_clicked()
{
    if(!isPressed[1]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            char c = temps.pop();
            float num = temps.pop()-100;
            float result = 0;
            qDebug() << num << c << cur[0];
            if(c == '+'){
                result = num + cur[0];
            }
            else if(c == '-'){
                result = num - cur[0];
            }
            else if(c == '*'){
                result = num * cur[0];
            }
            else if(c == '/'){
                result = num / cur[0];
            }
            if(isFloatInteger(result))ui->firstButton->setText(QString::number(std::round(result)));
            else ui->firstButton->setText(QString::number(result,'f',2));
            cur[0]=result;
            isPressed[1]=0;
            buttons[lastPressed]->setVisible(false);
            symbols[lastChar]->setStyleSheet(R"(
                                             QPushButton {
                                                 background-color:rgb(199, 199, 199);
                                             }
                                             QPushButton:hover {
                                                 background-color:rgb(107, 107, 107);
                                             }
                                             QPushButton:pressed{
                                                 background-color:rgb(50, 50, 50);
                                             }
                                           )");
            isPressed[lastChar+4]=0;
            count--;
            if(count == 1 && isFloatInteger(result) && std::round(result) == 24){
                message();
            }
            else if(count == 1){
                ui->firstButton->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(255, 0, 0);
                                                }
                                              )");
                QTimer::singleShot(500, this, SLOT(on_refreshButton_clicked()));
            }
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            buttons[lastPressed]->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(156, 156, 156);
                                                }
                                                QPushButton:hover {
                                                    background-color:rgb(107, 107, 107);
                                                }
                                                QPushButton:pressed{
                                                    background-color:rgb(50, 50, 50);
                                                }
                                            )");
            ui->firstButton->setStyleSheet(R"(
                                   #firstButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #firstButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #firstButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.pop();
            temps.push(cur[0]+100);
            isPressed[lastPressed]=0;
            isPressed[1] = 1;
            lastPressed = 1;
        }
        else{
            ui->firstButton->setStyleSheet(R"(
                                   #firstButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #firstButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #firstButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.push(cur[0]+100);
            isPressed[1] = 1;
            lastPressed = 1;
        }
    }
    else{
        if(!temps.isEmpty() && checkSymbol(temps.top())==true)if(lastPressed==1)return;
        ui->firstButton->setStyleSheet(R"(
                               #firstButton{
                                  background-color:rgb(156, 156, 156);
                               }

                               #firstButton:hover{
                                  background-color:rgb(107, 107, 107);
                               }

                               #firstButton::pressed{
                                  background-color:rgb(50, 50, 50);
                               }
                             )");
        temps.pop();
        isPressed[1]=0;
    }
}

void pokers::on_secondButton_clicked()
{
    if(!isPressed[2]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            char c = temps.pop();
            float num = temps.pop()-100;
            float result = 0;
            qDebug() << num << c << cur[1];
            if(c == '+'){
                result = num + cur[1];
            }
            else if(c == '-'){
                result = num - cur[1];
            }
            else if(c == '*'){
                result = num * cur[1];
            }
            else if(c == '/'){
                result = num / cur[1];
            }
            if(isFloatInteger(result))ui->secondButton->setText(QString::number(std::round(result)));
            else ui->secondButton->setText(QString::number(result,'f',2));
            cur[1]=result;
            isPressed[2]=0;
            buttons[lastPressed]->setVisible(false);
            symbols[lastChar]->setStyleSheet(R"(
                                             QPushButton {
                                                 background-color:rgb(199, 199, 199);
                                             }
                                             QPushButton:hover {
                                                 background-color:rgb(107, 107, 107);
                                             }
                                             QPushButton:pressed{
                                                 background-color:rgb(50, 50, 50);
                                             }
                                           )");
            isPressed[lastChar+4]=0;
            count--;
            if(count == 1 && isFloatInteger(result) && std::round(result) == 24){
                message();
            }
            else if(count == 1){
                ui->secondButton->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(255, 0, 0);
                                                }
                                              )");
                QTimer::singleShot(500, this, SLOT(on_refreshButton_clicked()));
            }
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            buttons[lastPressed]->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(156, 156, 156);
                                                }
                                                QPushButton:hover {
                                                    background-color:rgb(107, 107, 107);
                                                }
                                                QPushButton:pressed{
                                                    background-color:rgb(50, 50, 50);
                                                }
                                            )");
            ui->secondButton->setStyleSheet(R"(
                                   #secondButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #secondButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #secondButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.pop();
            temps.push(cur[1]+100);
            isPressed[lastPressed]=0;
            isPressed[2] = 1;
            lastPressed = 2;
        }
        else{
            ui->secondButton->setStyleSheet(R"(
                                   #secondButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #secondButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #secondButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.push(cur[1]+100);
            isPressed[2] = 1;
            lastPressed = 2;
        }
    }
    else{
        if(!temps.isEmpty() && checkSymbol(temps.top())==true)if(lastPressed==2)return;
        ui->secondButton->setStyleSheet(R"(
                               #secondButton{
                                  background-color:rgb(156, 156, 156);
                               }

                               #secondButton:hover{
                                  background-color:rgb(107, 107, 107);
                               }

                               #secondButton::pressed{
                                  background-color:rgb(50, 50, 50);
                               }
                             )");
        temps.pop();
        isPressed[2]=0;
    }
}

void pokers::on_thirdButton_clicked()
{
    if(!isPressed[3]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            char c = temps.pop();
            float num = temps.pop()-100;
            float result = 0;
            qDebug() << num << c << cur[2];
            if(c == '+'){
                result = num + cur[2];
            }
            else if(c == '-'){
                result = num - cur[2];
            }
            else if(c == '*'){
                result = num * cur[2];
            }
            else if(c == '/'){
                result = num / cur[2];
            }
            if(isFloatInteger(result))ui->thirdButton->setText(QString::number(std::round(result)));
            else ui->thirdButton->setText(QString::number(result,'f',2));
            cur[2]=result;
            isPressed[3]=0;
            buttons[lastPressed]->setVisible(false);
            symbols[lastChar]->setStyleSheet(R"(
                                             QPushButton {
                                                 background-color:rgb(199, 199, 199);
                                             }
                                             QPushButton:hover {
                                                 background-color:rgb(107, 107, 107);
                                             }
                                             QPushButton:pressed{
                                                 background-color:rgb(50, 50, 50);
                                             }
                                           )");
            isPressed[lastChar+4]=0;
            count--;
            if(count == 1 && isFloatInteger(result) && std::round(result) == 24){
                message();
            }
            else if(count == 1){
                ui->thirdButton->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(255, 0, 0);
                                                }
                                              )");
                QTimer::singleShot(500, this, SLOT(on_refreshButton_clicked()));
            }
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            buttons[lastPressed]->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(156, 156, 156);
                                                }
                                                QPushButton:hover {
                                                    background-color:rgb(107, 107, 107);
                                                }
                                                QPushButton:pressed{
                                                    background-color:rgb(50, 50, 50);
                                                }
                                            )");
            ui->thirdButton->setStyleSheet(R"(
                                   #thirdButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #thirdButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #thirdButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.pop();
            temps.push(cur[2]+100);
            isPressed[lastPressed]=0;
            isPressed[3] = 1;
            lastPressed = 3;
        }
        else{
            ui->thirdButton->setStyleSheet(R"(
                                   #thirdButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #thirdButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #thirdButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.push(cur[2]+100);
            isPressed[3] = 1;
            lastPressed = 3;
        }
    }
    else{
        if(!temps.isEmpty() && checkSymbol(temps.top())==true)if(lastPressed==3)return;
        ui->thirdButton->setStyleSheet(R"(
                               #thirdButton{
                                  background-color:rgb(156, 156, 156);
                               }

                               #thirdButton:hover{
                                  background-color:rgb(107, 107, 107);
                               }

                               #thirdButton::pressed{
                                  background-color:rgb(50, 50, 50);
                               }
                             )");
        temps.pop();
        isPressed[3]=0;
    }
}

void pokers::on_fourthButton_clicked()
{
    if(!isPressed[4]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            char c = temps.pop();
            float num = temps.pop()-100;
            float result = 0;
            qDebug() << num << c << cur[3];
            if(c == '+'){
                result = num + cur[3];
            }
            else if(c == '-'){
                result = num - cur[3];
            }
            else if(c == '*'){
                result = num * cur[3];
            }
            else if(c == '/'){
                result = num / cur[3];
            }
            if(isFloatInteger(result))ui->fourthButton->setText(QString::number(std::round(result)));
            else ui->fourthButton->setText(QString::number(result,'f',2));
            cur[3]=result;
            isPressed[4]=0;
            buttons[lastPressed]->setVisible(false);
            symbols[lastChar]->setStyleSheet(R"(
                                             QPushButton {
                                                 background-color:rgb(199, 199, 199);
                                             }
                                             QPushButton:hover {
                                                 background-color:rgb(107, 107, 107);
                                             }
                                             QPushButton:pressed{
                                                 background-color:rgb(50, 50, 50);
                                             }
                                           )");
            isPressed[lastChar+4]=0;
            count--;
            if(count == 1 && isFloatInteger(result) && std::round(result) == 24){
                message();
            }
            else if(count == 1){
                ui->fourthButton->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(255, 0, 0);
                                                }
                                              )");
                QTimer::singleShot(500, this, SLOT(on_refreshButton_clicked()));
            }
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            buttons[lastPressed]->setStyleSheet(R"(
                                                QPushButton {
                                                    background-color:rgb(156, 156, 156);
                                                }
                                                QPushButton:hover {
                                                    background-color:rgb(107, 107, 107);
                                                }
                                                QPushButton:pressed{
                                                    background-color:rgb(50, 50, 50);
                                                }
                                            )");
            ui->fourthButton->setStyleSheet(R"(
                                   #fourthButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #fourthButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #fourthButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.pop();
            temps.push(cur[3]+100);
            isPressed[lastPressed]=0;
            isPressed[4] = 1;
            lastPressed = 4;
        }
        else{
            ui->fourthButton->setStyleSheet(R"(
                                   #fourthButton{
                                       background-color:rgb(203, 135, 0);
                                   }

                                   #fourthButton::hover{
                                       background-color:rgb(179, 119, 58);
                                   }

                                   #fourthButton::pressed{
                                       background-color:rgb(143, 97, 57);
                                   }

                                 )");
            temps.push(cur[3]+100);
            isPressed[4] = 1;
            lastPressed = 4;
        }
    }
    else{
        if(!temps.isEmpty() && checkSymbol(temps.top())==true)if(lastPressed==4)return;
        ui->fourthButton->setStyleSheet(R"(
                               #fourthButton{
                                  background-color:rgb(156, 156, 156);
                               }

                               #fourthButton:hover{
                                  background-color:rgb(107, 107, 107);
                               }

                               #fourthButton::pressed{
                                  background-color:rgb(50, 50, 50);
                               }
                             )");
        temps.pop();
        isPressed[4]=0;
    }
}

void pokers::on_addButton_clicked()
{
    if(!isPressed[5]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            ui->addButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            temps.push('+');
            lastChar = 1;
            isPressed[5]=1;
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            ui->addButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            symbols[lastChar]->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            isPressed[lastChar+4]=0;
            temps.pop();
            temps.push('+');
            lastChar = 1;
            isPressed[5]=1;
        }
    }
    else{
        if(!temps.isEmpty() && temps.top()=='+'){
            ui->addButton->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            temps.pop();
            isPressed[5]=0;
        }
    }
}

void pokers::on_subButton_clicked()
{
    if(!isPressed[6]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            ui->subButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            temps.push('-');
            lastChar = 2;
            isPressed[6]=1;
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            ui->subButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            symbols[lastChar]->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            isPressed[lastChar+4]=0;
            temps.pop();
            temps.push('-');
            lastChar = 2;
            isPressed[6]=1;
        }
    }
    else{
        if(!temps.isEmpty() && temps.top()=='-'){
            ui->subButton->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            temps.pop();
            isPressed[6]=0;
        }
    }
}

void pokers::on_plusButton_clicked()
{
    if(!isPressed[7]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            ui->plusButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            temps.push('*');
            lastChar = 3;
            isPressed[7]=1;
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            ui->plusButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            symbols[lastChar]->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            isPressed[lastChar+4]=0;
            temps.pop();
            temps.push('*');
            lastChar = 3;
            isPressed[7]=1;
        }
    }
    else{
        if(!temps.isEmpty() && temps.top()=='*'){
            ui->plusButton->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            temps.pop();
            isPressed[7]=0;
        }
    }
}

void pokers::on_divButton_clicked()
{
    if(!isPressed[8]){
        if(!temps.isEmpty() && checkSymbol(temps.top())==false){
            ui->divButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            temps.push('/');
            lastChar = 4;
            isPressed[8]=1;
        }
        else if(!temps.isEmpty() && checkSymbol(temps.top())==true){
            ui->divButton->setStyleSheet(R"(
                                         QPushButton {
                                             background-color:rgb(203, 135, 0);
                                         }
                                         QPushButton:hover {
                                             background-color:rgb(179, 119, 58);
                                         }
                                         QPushButton:pressed{
                                             background-color:rgb(143, 97, 57);
                                         }
                                     )");
            symbols[lastChar]->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            isPressed[lastChar+4]=0;
            temps.pop();
            temps.push('/');
            lastChar = 4;
            isPressed[8]=1;
        }
    }
    else{
        if(!temps.isEmpty() && temps.top()=='/'){
            ui->divButton->setStyleSheet(R"(
                                          QPushButton {
                                              background-color:rgb(199, 199, 199);
                                          }
                                          QPushButton:hover {
                                              background-color:rgb(107, 107, 107);
                                          }
                                          QPushButton:pressed{
                                              background-color:rgb(50, 50, 50);
                                          }
                                      )");
            temps.pop();
            isPressed[8]=0;
        }
    }
}

void pokers::on_refreshButton_clicked()
{
    for(int i = 1;i < 5;i++){
        buttons[i]->setVisible(true);
        buttons[i]->setText(QString::number(resNums[i-1]));
        cur[i-1]=resNums[i-1];
        buttons[i]->setStyleSheet(R"(
                                    QPushButton {
                                       background-color:rgb(156, 156, 156);
                                    }
                                    QPushButton:hover {
                                       background-color:rgb(107, 107, 107);
                                    }
                                    QPushButton:pressed{
                                       ackground-color:rgb(50, 50, 50);
                                    }
                                  )");
        symbols[i]->setStyleSheet(R"(
                                    QPushButton {
                                       background-color:rgb(199, 199, 199);
                                    }
                                    QPushButton:hover {
                                       background-color:rgb(107, 107, 107);
                                    }
                                    QPushButton:pressed{
                                       ackground-color:rgb(50, 50, 50);
                                    }
                                  )");
    }
    for(int i = 0;i < 10;i++){
        isPressed[i]=0;
    }
    temps.clear();
    lastPressed = -1;
    lastChar = -1;
    count = 4;
}

void pokers::on_retButton_clicked()
{
    cha->show();
    delete this;
}

void pokers::on_answerButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("本题答案");
    msgBox.setText(answer);
    msgBox.setStandardButtons(QMessageBox::Save);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setButtonText(QMessageBox::Save, "继续挑战");
    msgBox.exec();
}
