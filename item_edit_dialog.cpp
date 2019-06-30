#include <QLabel>
#include <QVBoxLayout>

#include "item_edit_dialog.h"

ItemEditDialog::ItemEditDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("About"));

    auto *Help = new QWidget(this);
    auto *layout = new QVBoxLayout(this);
    auto *text = new QLabel(Help);
    text->setText(tr("Currency-Converter v2.0"));
    layout->addWidget(text, 0, Qt::AlignHCenter);
}

ItemEditDialog::~ItemEditDialog()
{
}
