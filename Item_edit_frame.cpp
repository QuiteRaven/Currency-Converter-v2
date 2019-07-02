#include "Item_Edit_Frame.h"
#include "currency_type.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QDoubleValidator>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDate>

const QString API_KEY = "5e77529f0adfeacd8f2b";

ItemEditFrame::ItemEditFrame(QWidget *parent)
    :QFrame(parent)
{
    _networkManager = new QNetworkAccessManager(this);
    connect(_networkManager, &QNetworkAccessManager::finished, this, &ItemEditFrame::onResult);
    
    auto today = QDate::currentDate();
    auto late = QDate(2018,06,01);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *layout = new QVBoxLayout(this);

    auto *layout_A = new QHBoxLayout();
    layout->addLayout(layout_A);
    _fieldDate = new QDateEdit(this);
    _fieldDate->setDisplayFormat("yyyy-MM-dd");
    _fieldDate->setMaximumDate(today);
    _fieldDate->setMinimumDate(late);
    _fieldDate->setDate(today);
    layout_A->addWidget(_fieldDate, 0, Qt::AlignHCenter);

    auto *layout_B = new QHBoxLayout();
    layout->addLayout(layout_B);
    auto *lable_B = new QLabel(this);
    lable_B->setText(tr("From"));
    layout_B->addWidget(lable_B);
    setup_currency_From(layout_B);
    auto *lable_C = new QLabel(this);
    lable_C->setMargin(0);
    lable_C->setText(tr("To"));
    layout_B->addWidget(lable_C);
    setup_currency_To(layout_B);
    
    auto *layout_C = new QHBoxLayout();
    layout->addLayout(layout_C);
    auto *inputRange = new QDoubleValidator(this);
    inputRange->setBottom(0);
    _fieldFrom = new QLineEdit(this);
    _fieldFrom->setMaxLength(20);
    _fieldFrom->setPlaceholderText("Enter value");
    _fieldFrom->setValidator(inputRange);
    connect(_fieldFrom, &QLineEdit::textChanged, this, &ItemEditFrame::onTextChanged);
    layout_C->addWidget(_fieldFrom);
    _fieldTo = new QLineEdit(this);
    _fieldTo->setMaxLength(20);
    _fieldTo->setReadOnly(true);
    layout_C->addWidget(_fieldTo);

    auto *layout_D = new QHBoxLayout();
    layout->addLayout(layout_D);
    _convertButton = new QPushButton(this);
    layout->addWidget(_convertButton,0,Qt::AlignHCenter);
    _convertButton->setText(tr("Convert"));
    _convertButton->setEnabled(false);
    connect(_convertButton, &QPushButton::clicked, this,&ItemEditFrame::onConvertButton);
}

void ItemEditFrame::setup_currency_From(QLayout *currency)
{
    auto *layout = new QHBoxLayout();
    currency->addItem(layout);

    _dropList_From = new QComboBox(this);
    _dropList_From->addItem(tr("USD"), USD);
    _dropList_From->addItem(tr("EUR"), EUR);
    _dropList_From->addItem(tr("GBP"), GBP);
    _dropList_From->addItem(tr("JPY"), JPY);
    _dropList_From->addItem(tr("KZT"), KZT);
    _dropList_From->addItem(tr("RUB"), RUB);
    layout->addWidget(_dropList_From);
}

void ItemEditFrame::setup_currency_To(QLayout *currency)
{
    auto *layout = new QHBoxLayout();
    currency->addItem(layout);

    _dropList_To = new QComboBox(this);
    _dropList_To->addItem(tr("USD"), USD);
    _dropList_To->addItem(tr("EUR"), EUR);
    _dropList_To->addItem(tr("GBP"), GBP);
    _dropList_To->addItem(tr("JPY"), JPY);
    _dropList_To->addItem(tr("KZT"), KZT);
    _dropList_To->addItem(tr("RUB"), RUB);
    layout->addWidget(_dropList_To);
}

void ItemEditFrame::onConvertButton()
{
        from = _dropList_From->currentText();
        to = _dropList_To->currentText();
        date = _fieldDate->text();
        QUrl url;
        url = QString("http://free.currconv.com/api/v7/convert?q=%3_%4&compact=ultra&date=%1&apiKey=%2")
            .arg(date).arg(API_KEY).arg(from).arg(to);
        _networkManager->get(QNetworkRequest(url));
}

void ItemEditFrame::onResult(QNetworkReply *reply)
{
    if (!reply->error()) 
    {
        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = json.object();
        QJsonObject jsonObjValue = jsonObj.value(from + "_" + to).toObject();
        double rate = jsonObjValue.value(date).toDouble();
        double amount = _fieldFrom->text().toDouble();
        double result = amount * rate;
        _fieldTo->setText(QString::number(result,0,3)); 
    }
    else
        QMessageBox::warning(this, "Error", "Connection lost).");
}

void ItemEditFrame::onTextChanged()
{
    if (_fieldFrom->text() != "")
    {
        _convertButton->setEnabled(true);
    }
    else
        _convertButton->setEnabled(false);
}

ItemEditFrame::~ItemEditFrame()
{
}