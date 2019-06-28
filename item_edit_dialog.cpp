#include "item_edit_dialog.h"

#include <QLabel>
#include <QHBoxLayout>

ItemEditDialog::ItemEditDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("About"));

    QFrame *Help = new QFrame(this);
    QHBoxLayout *layout = new QHBoxLayout(Help);
    QLabel *text = new QLabel(Help);
    text->setText(tr("GAME OF THE YEAR"));
    layout->addWidget(text, 0, Qt::AlignBottom);
}

ItemEditDialog::~ItemEditDialog()
{
}
