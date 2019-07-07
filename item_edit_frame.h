#ifndef ITEMEDITFRAME_H
#define ITEMEDITFRAME_H

#include <QFrame>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QFile>
#include <QJsonDocument>

class ItemEditFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ItemEditFrame(QWidget *parent = nullptr);
    ~ItemEditFrame();

private:
    void setup_currency_From(QLayout *currency);
    void setup_currency_To(QLayout *currency);
    void onResult(QNetworkReply *reply);
    void onConvertButton();
    void onTextChanged();
    void toWriteinFile();

private:
    QNetworkAccessManager * _networkManager;
    QPushButton            * _convertButton;
    
    QDateEdit * _fieldDate;
    QLineEdit * _fieldFrom;
    QLineEdit * _fieldTo;
    QComboBox * _dropList_From;
    QComboBox * _dropList_To;
   
    QJsonDocument doc;
    QFile file;
    QString from;
    QString to;
    QString date;
};
#endif