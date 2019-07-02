#include "about_dialog.h"

#include <QLabel>
#include <QVBoxLayout>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent,Qt::WindowCloseButtonHint)
{
    QDialog::setFixedSize(200, 100);
    setWindowTitle(tr("About"));
    auto *Help = new QWidget(this);
    auto *layout = new QVBoxLayout(this);
    auto *text = new QLabel(Help);
    text->setText(tr("Currency-Converter v2.0"));
    layout->addWidget(text, 0, Qt::AlignHCenter);
}

AboutDialog::~AboutDialog()
{
}
