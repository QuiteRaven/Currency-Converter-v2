#ifndef ITEMEDITFRAME_H
#define ITEMEDITFRAME_H

#include <QFrame>
#include <QDoubleValidator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>

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

private:
    QNetworkAccessManager * _networkManager;
    QPushButton            * _convertButton;

    QLineEdit * _fieldDate;
    QLineEdit * _fieldFrom;
    QLineEdit * _fieldTo;
    QComboBox * _dropList_From;
    QComboBox * _dropList_To;

    QString from;
    QString to;
    QString date;
};
#endif