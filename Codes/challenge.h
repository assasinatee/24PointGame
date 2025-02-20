#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <QWidget>
#include <widget.h>
#include <QLCDNumber>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class challenge;
}

class challenge : public QWidget
{
    Q_OBJECT

public:
    explicit challenge(Widget*mainWidget, QWidget *parent = nullptr);
    ~challenge();

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap pixmap("../images/background2.jpg");
        pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pixmap);
    }

private slots:
    void on_breakButton_clicked();

    void on_timingButton_clicked();

    void on_retButton_clicked();

private:
    Ui::challenge *ui;
    Widget *w;
};

#endif // CHALLENGE_H
