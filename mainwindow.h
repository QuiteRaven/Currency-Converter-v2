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

  void onAbout();

private:
    QAction	         * _aboutAction = nullptr;
    ItemEditFrame        *_mainFrame = nullptr;
};
#endif