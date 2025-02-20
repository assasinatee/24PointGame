#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void processQString(const QString &input,const QString addr);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        QPixmap pixmap("../images/background.jpg");
        pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pixmap);
    }

private slots:
    void on_onceButton_clicked();

    void on_fileButton_clicked();

    void on_challengeButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
