#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // 启用高 DPI 缩放
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling, false);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);    // 启用高 DPI 图像支持
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");
    qputenv("QT_SCALE_FACTOR", "1");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication a(argc, argv);
    QFont font("Arial", 12);
    a.setFont(font);
    Widget w;
    w.show();
    return a.exec();
}
