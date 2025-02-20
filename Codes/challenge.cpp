#include "challenge.h"
#include "ui_challenge.h"
#include "pokers.h"

challenge::challenge(Widget*mainWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::challenge)
{
    ui->setupUi(this);

    w = mainWidget;

}

challenge::~challenge()
{
    delete ui;
}



void challenge::on_breakButton_clicked()
{
    this->hide();
    pokers *p = new pokers(this);
    p->show();
}


void challenge::on_timingButton_clicked()
{
    this->hide();
    pokers *p = new pokers(this,1,1);
    p->show();
}

void challenge::on_retButton_clicked()
{
    w->show();
    delete this;
}
