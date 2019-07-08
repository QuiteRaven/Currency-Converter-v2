#include "Item_Edit_Frame.h"
#include "currency_type.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QDoubleValidator>
#include <QtNetwork/QNetworkRequest>
#include <QJsonObject>
#include <QMessageBox>
#include <QDate>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QJsonArray>

const QString API_KEY = "5e77529f0adfeacd8f2b";

ItemEditFrame::ItemEditFrame(QWidget *parent)
    :QFrame(parent)
{
    _networkManager = new QNetworkAccessManager(this);
    connect(_networkManager, &QNetworkAccessManager::finished, this, &ItemEditFrame::onResult);  
  
    auto mainlayout = new QVBoxLayout(this);
    createDateEdit();
    mainlayout->addLayout(_layoutDate);   
    createCboxEdit();
    mainlayout->addLayout(_layoutCbox);
    createFieldsEdit();
    mainlayout->addLayout(_layoutFields);
    createButtonEdit();
    mainlayout->addLayout(_layoutButton);
}

void ItemEditFrame::setupcurrencyFrom(QLayout *currency)
{
    _dropListFrom = new QComboBox();
    _dropListFrom->addItem(tr("USD"), USD);
    _dropListFrom->addItem(tr("EUR"), EUR);
    _dropListFrom->addItem(tr("GBP"), GBP);
    _dropListFrom->addItem(tr("JPY"), JPY);
    _dropListFrom->addItem(tr("KZT"), KZT);
    _dropListFrom->addItem(tr("RUB"), RUB);
    _dropListFrom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void ItemEditFrame::setupcurrencyTo(QLayout *currency)
{
    _dropListTo = new QComboBox();
    _dropListTo->addItem(tr("USD"), USD);
    _dropListTo->addItem(tr("EUR"), EUR);
    _dropListTo->addItem(tr("GBP"), GBP);
    _dropListTo->addItem(tr("JPY"), JPY);
    _dropListTo->addItem(tr("KZT"), KZT);
    _dropListTo->addItem(tr("RUB"), RUB);
    _dropListTo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
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

        toWriteinFile();
    }
    else
        QMessageBox::warning(this, "Error", "Network error.");
}

void ItemEditFrame::onConvertButton()
{
    from = _dropListFrom->currentText();
    to = _dropListTo->currentText();
    date = _fieldDate->text();
    QUrl url;
    url = QString("http://free.currconv.com/api/v7/convert?q=%3_%4&compact=ultra&date=%1&apiKey=%2")
        .arg(date).arg(API_KEY).arg(from).arg(to);
    _networkManager->get(QNetworkRequest(url));
}

void ItemEditFrame::onTextChanged()
{
    if (_fieldFrom->text() != "")
    
        _convertButton->setEnabled(true);
    
    else
        _convertButton->setEnabled(false);
}

void ItemEditFrame::toWriteinFile()
{
    file.setFileName("History.json");
    file.open(QIODevice::ReadOnly | QFile::Text);
    doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QVariantMap map;
        map.insert("Date", _fieldDate->text());
        map.insert("From-To", from + "-" + to);
        map.insert("Result", _fieldFrom->text() + "=" + _fieldTo->text());
        auto object = QJsonObject::fromVariantMap(map);
        QJsonArray toWrite = doc.object().value("Currency").toArray();
        toWrite.append(object);
        doc.setArray(toWrite);
        file.write("{\"Currency\":" + doc.toJson() + "}");
        file.close();
    }
    else
    {
        QMessageBox::warning(this, "Error", "File don't open.");
    }
}

void ItemEditFrame::createDateEdit()
{
    auto today = QDate::currentDate();
    auto border = today.addYears(-1);
    _layoutDate = new QHBoxLayout();
    _layoutDate->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto label_Date = new QLabel(this);
    label_Date->setText(tr("Date"));
    _layoutDate->addWidget(label_Date);
    _fieldDate = new QDateEdit(this);
    _fieldDate->setDisplayFormat("yyyy-MM-dd");
    _fieldDate->setMaximumDate(today);
    _fieldDate->setMinimumDate(border);
    _fieldDate->setDate(today);
    _layoutDate->addWidget(_fieldDate, 0, Qt::AlignHCenter);
    _layoutDate->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
}

void ItemEditFrame::createCboxEdit()
{
    _layoutCbox = new QHBoxLayout();
    auto label_From = new QLabel(this);
    label_From->setText(tr("From"));
    _layoutCbox->addWidget(label_From);
    setupcurrencyFrom(_layoutCbox);
    _layoutCbox->addWidget(_dropListFrom);
    _layoutCbox->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto *lable_To = new QLabel(this);
    lable_To->setText(tr("To"));
    _layoutCbox->addWidget(lable_To);
    setupcurrencyTo(_layoutCbox);
    _layoutCbox->addWidget(_dropListTo);
}

void ItemEditFrame::createFieldsEdit()
{
    _layoutFields = new QHBoxLayout();
    auto inputRange = new QDoubleValidator(this);
    inputRange->setBottom(0);
    auto label_From2 = new QLabel(this);
    label_From2->setText(tr("From"));
    _layoutFields->addWidget(label_From2);
    _fieldFrom = new QLineEdit(this);
    _fieldFrom->setMaxLength(20);
    _fieldFrom->setPlaceholderText("Enter value");
    _fieldFrom->setValidator(inputRange);
    connect(_fieldFrom, &QLineEdit::textChanged, this, &ItemEditFrame::onTextChanged);
    _layoutFields->addWidget(_fieldFrom);
    _layoutFields->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto label_To2 = new QLabel(this);
    label_To2->setText(tr("To"));
    _layoutFields->addWidget(label_To2);
    _fieldTo = new QLineEdit(this);
    _fieldTo->setReadOnly(true);
    _fieldTo->setFrame(false);
    _fieldTo->setFocusPolicy(Qt::NoFocus);
    _layoutFields->addWidget(_fieldTo);
}

void ItemEditFrame::createButtonEdit()
{
    _layoutButton = new QHBoxLayout();
    _convertButton = new QPushButton(this);
    _layoutButton->addWidget(_convertButton, 0, Qt::AlignHCenter);
    _convertButton->setText(tr("Convert"));
    _convertButton->setEnabled(false);
    connect(_convertButton, &QPushButton::clicked, this, &ItemEditFrame::onConvertButton);
}

ItemEditFrame::~ItemEditFrame()
{

}