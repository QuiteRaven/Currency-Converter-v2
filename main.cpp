#include "MainWindow.h"

#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto *Picture = new QSplashScreen;
    Picture->setPixmap(QPixmap(":/2.png"));
    Picture->show();
    MainWindow window;
    QTimer::singleShot(3000, nullptr, [&window,Picture]()
    {
        Picture->close();
        delete Picture;
        window.show();
    });
    return app.exec();
}
