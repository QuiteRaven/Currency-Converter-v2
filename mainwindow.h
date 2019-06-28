#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Item_Edit_Frame.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void onNewItem();

private:
    QAction	         * _actNewItem = nullptr;
    ItemEditFrame        *_upFrame = nullptr;
};
#endif