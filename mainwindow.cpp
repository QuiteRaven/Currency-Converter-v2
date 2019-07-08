#include "MainWindow.h"
#include "about_dialog.h"

#include <QMenuBar>
#include <QAction>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMainWindow::setMaximumSize(500, 300);
    setWindowTitle(tr("Currency-Converter"));

    auto centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    auto layout = new QVBoxLayout(centralWidget);

    _mainFrame = new ItemEditFrame(this);
    layout->addWidget(_mainFrame);

    _aboutAction = new QAction(this);
    _aboutAction->setText(tr("About"));
    connect(_aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    QMenu *mItem = menuBar()->addMenu(tr("Help"));
    mItem->addAction(_aboutAction);
}

void MainWindow::onAbout()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

MainWindow::~MainWindow()
{

}
