#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include <widget.h>
#include <oncecalculate.h>

namespace Ui {
class result;
}

class result : public QWidget
{
    Q_OBJECT

public:
    explicit result(Widget*mainWidget=nullptr, onceCalculate*mainOnce=nullptr,QWidget *parent = nullptr);
    ~result();
    void showHave(QString a);
    void showNotHave();

private slots:
    void on_retButton_clicked();

    void on_continueButton_clicked();

private:
    Ui::result *ui;
    Widget *w;
    onceCalculate *o;
};

#endif // RESULT_H
