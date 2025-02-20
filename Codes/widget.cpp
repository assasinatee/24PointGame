#include "widget.h"
#include "ui_widget.h"
#include "oncecalculate.h"
#include "challenge.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_onceButton_clicked()
{
    this->hide();
    onceCalculate *once = new onceCalculate(this);
    once->show();
}

void Widget::processQString(const QString &input,const QString addr) {
    QStringList lines = input.split('\n'); // 按照换行符分割字符串
    QString result;
    bool flag = 1;
    for (const QString &line : lines) {
        QStringList numbers = line.split(' '); // 假设数字之间用空格分隔
        if (numbers.size() == 4) {
            bool ok1, ok2, ok3, ok4;
            int num1 = numbers[0].toInt(&ok1);
            int num2 = numbers[1].toInt(&ok2);
            int num3 = numbers[2].toInt(&ok3);
            int num4 = numbers[3].toInt(&ok4);


            if (ok1 && ok2 && ok3 && ok4) {
                double ini[4];
                QString strs[4];
                ini[0]=(double)num1;
                ini[1]=(double)num2;
                ini[2]=(double)num3;
                ini[3]=(double)num4;
                strs[0]=QString::number(num1);
                strs[1]=QString::number(num2);
                strs[2]=QString::number(num3);
                strs[3]=QString::number(num4);

                for(int i = 0;i < 4;i++){
                    result += strs[i];
                    result += ' ';
                }

                if (d24(ini,strs,4)) {
                    result += strs[0];
                    result += "=24";
                    result += '\n';
                } else {
                    result += "无法计算24点";
                    result += '\n';
                }
            } else {
                for(int i = 0;i < 4;i++){
                    result += numbers[i];
                    result += ' ';
                }
                result.chop(2);
                result += ' ';
                result += "输入不为数字";
                result += '\n';
                flag = 0;
            }
        } else {
            for(int i = 0;i < numbers.size();i++){
                result += numbers[i];
                result += ' ';
            }
            result.chop(2);
            result += ' ';
            result += "输入个数不为4";
            result += '\n';
            flag = 0;
        }
    }
    if(flag){
        QMessageBox::information(this, "通知", "计算成功");
    }
    else{
        QMessageBox::information(this, "通知", "部分输入有误");
    }

    QString filename;
    int dotPos = addr.lastIndexOf('.');
    if (dotPos == -1) {
        filename =  addr + "_res";
    } else {
        QString baseName = addr.left(dotPos);
        QString extension = addr.mid(dotPos);
        filename =  addr + "_res" + extension;
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件进行写入:" << file.errorString();
    }
    QTextStream out(&file);
    out << result;
    file.close();
}

void Widget::on_fileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "选择一个文件","../","*.txt");
    if(filename.isEmpty()){
        return;
    }
    else{
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        QString string = QString::fromUtf8(ba);
        processQString(string,filename);
        file.close();
    }

}

void Widget::on_challengeButton_clicked()
{
    this->hide();
    challenge* c = new challenge(this);
    c->show();
}
