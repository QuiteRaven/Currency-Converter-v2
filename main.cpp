#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto *kianuPicture = new QSplashScreen;
    kianuPicture->setPixmap(QPixmap(":/Kianu/Resources/1.jpg"));
    kianuPicture->show();
    MainWindow window;
    QTimer::singleShot(3000, kianuPicture, SLOT(close()));
    QTimer::singleShot(3000, &window, SLOT(show()));
    return app.exec();
}
