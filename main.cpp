#include <QApplication>
#include <QHBoxLayout>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(800, 480);
    w.setStyleSheet("background-image: url(./graphics/background_native.png);");
    w.show();

    return app.exec();
}

void quitApp(QGuiApplication app) {
    app.exit();
}
