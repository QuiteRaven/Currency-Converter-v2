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
#include <QHBoxLayout>
class ItemEditFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ItemEditFrame(QWidget *parent = nullptr);
    ~ItemEditFrame();

private:
    void setupcurrencyFrom(QLayout *currency);
    void setupcurrencyTo(QLayout *currency);
    void onResult(QNetworkReply *reply);
    void onConvertButton();
    void onTextChanged();
    void toWriteinFile();
    void createDateEdit();
    void createCboxEdit();
    void createFieldsEdit();
    void createButtonEdit();

private:
    QNetworkAccessManager * _networkManager;
    QPushButton            * _convertButton;
    
    QDateEdit * _fieldDate;
    QLineEdit * _fieldFrom;
    QLineEdit * _fieldTo;
    QComboBox * _dropListFrom;
    QComboBox * _dropListTo;
    QHBoxLayout * _layoutDate;
    QHBoxLayout * _layoutCbox;
    QHBoxLayout * _layoutFields;
    QHBoxLayout * _layoutButton;
   
    QJsonDocument doc;
    QFile file;
    QString from;
    QString to;
    QString date;
};
#endif