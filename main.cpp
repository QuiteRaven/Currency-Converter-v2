#include "MainWindow.h"

#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto *kianuPicture = new QSplashScreen;
    kianuPicture->setPixmap(QPixmap(":/Kianu/Resources/2.png"));
    kianuPicture->show();
    MainWindow window;
    QTimer::singleShot(3000, nullptr, [&window,kianuPicture]()
    {
        kianuPicture->close();
        delete kianuPicture;
        window.show();
    });
    return app.exec();
}
