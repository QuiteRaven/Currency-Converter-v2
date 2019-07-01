#ifndef ITEMEDITDIALOG_H
#define ITEMEDITDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog
{
public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();
};
#endif
