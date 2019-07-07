#include "Item_Edit_Frame.h"
#include "currency_type.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
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
    auto today = QDate::currentDate();
    auto border = today.addYears(-1);
   
    auto *mainlayout = new QVBoxLayout(this);

    auto *layout_Date = new QHBoxLayout();
    mainlayout->addLayout(layout_Date);
    layout_Date->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto *label_Date = new QLabel(this);
    label_Date->setText(tr("Date"));
    layout_Date->addWidget(label_Date);
    _fieldDate = new QDateEdit(this);
    _fieldDate->setDisplayFormat("yyyy-MM-dd");
    _fieldDate->setMaximumDate(today);
    _fieldDate->setMinimumDate(border);
    _fieldDate->setDate(today);
    layout_Date->addWidget(_fieldDate, 0, Qt::AlignHCenter);
    layout_Date->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    auto *layout_Cbox = new QHBoxLayout();
    mainlayout->addLayout(layout_Cbox);
    auto *label_From = new QLabel(this);
    label_From->setText(tr("From"));
    layout_Cbox->addWidget(label_From);
    setup_currency_From(layout_Cbox);
    layout_Cbox->addWidget(_dropList_From);
    layout_Cbox->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto *lable_To = new QLabel(this);
    lable_To->setText(tr("To"));
    layout_Cbox->addWidget(lable_To);
    setup_currency_To(layout_Cbox);
    layout_Cbox->addWidget(_dropList_To);

    auto *layout_fields = new QHBoxLayout();
    mainlayout->addLayout(layout_fields);
    auto *inputRange = new QDoubleValidator(this);
    inputRange->setBottom(0);
    auto *label_From2 = new QLabel(this);
    label_From2->setText(tr("From"));
    layout_fields->addWidget(label_From2);
    _fieldFrom = new QLineEdit(this);
    _fieldFrom->setMaxLength(20);
    _fieldFrom->setPlaceholderText("Enter value");
    _fieldFrom->setValidator(inputRange);
    connect(_fieldFrom, &QLineEdit::textChanged, this, &ItemEditFrame::onTextChanged);
    layout_fields->addWidget(_fieldFrom);
    layout_fields->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    auto *label_To2 = new QLabel(this);
    label_To2->setText(tr("To"));
    layout_fields->addWidget(label_To2);
    _fieldTo = new QLineEdit(this);
    _fieldTo->setReadOnly(true);
    _fieldTo->setFrame(false);
    _fieldTo->setFocusPolicy(Qt::NoFocus);
    layout_fields->addWidget(_fieldTo);

    auto *layout_Button = new QHBoxLayout();
    mainlayout->addLayout(layout_Button);
    _convertButton = new QPushButton(this);
    layout_Button->addWidget(_convertButton,0,Qt::AlignHCenter);
    _convertButton->setText(tr("Convert"));
    _convertButton->setEnabled(false);
    connect(_convertButton, &QPushButton::clicked, this,&ItemEditFrame::onConvertButton);
}

void ItemEditFrame::setup_currency_From(QLayout *currency)
{
    _dropList_From = new QComboBox();
    _dropList_From->addItem(tr("USD"), USD);
    _dropList_From->addItem(tr("EUR"), EUR);
    _dropList_From->addItem(tr("GBP"), GBP);
    _dropList_From->addItem(tr("JPY"), JPY);
    _dropList_From->addItem(tr("KZT"), KZT);
    _dropList_From->addItem(tr("RUB"), RUB);
    _dropList_From->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void ItemEditFrame::setup_currency_To(QLayout *currency)
{
    _dropList_To = new QComboBox();
    _dropList_To->addItem(tr("USD"), USD);
    _dropList_To->addItem(tr("EUR"), EUR);
    _dropList_To->addItem(tr("GBP"), GBP);
    _dropList_To->addItem(tr("JPY"), JPY);
    _dropList_To->addItem(tr("KZT"), KZT);
    _dropList_To->addItem(tr("RUB"), RUB);
    _dropList_To->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
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

        toWriteinFile();
    }
    else
        QMessageBox::warning(this, "Error", "Connection lost.");
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

ItemEditFrame::~ItemEditFrame()
{

}