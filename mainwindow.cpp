#include "MainWindow.h"
#include "item_edit_dialog.h"

#include <QMenuBar>
#include <QAction>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Currency-Converter"));

    auto *frame = new QWidget();
    setCentralWidget(frame);
    auto *layout = new QVBoxLayout(frame);

    _upFrame = new ItemEditFrame(this);
    layout->addWidget(_upFrame);

    _actNewItem = new QAction(this);
    _actNewItem->setText(tr("About"));
    connect(_actNewItem, &QAction::triggered, this, &MainWindow::onNewItem);
    QMenu *mItem = menuBar()->addMenu(tr("Help"));
    mItem->addAction(_actNewItem);
}

void MainWindow::onNewItem() {
    ItemEditDialog aboutDialog(this);
    aboutDialog.exec();
}

MainWindow::~MainWindow()
{

}