#include "result.h"
#include "ui_result.h"

result::result(Widget*mainWidget, onceCalculate *mainOnce,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
    w = mainWidget;
    o = mainOnce;
}

result::~result()
{
    delete ui;
}

void result::showHave(QString a){
    ui->label->setText("结果为：");
    ui->label_2->setText(a);
}

void result::showNotHave(){
    ui->label->setText("");
    ui->label_2->setText("这四个数无法算出24点！");
}

void result::on_retButton_clicked()
{
    w->show();
    delete o;
    delete this;
}

void result::on_continueButton_clicked()
{
    o->show();
    delete this;
}
