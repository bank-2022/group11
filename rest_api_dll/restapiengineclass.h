#ifndef RESTAPIENGINECLASS_H
#define RESTAPIENGINECLASS_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QVector>

class RestApiEngineClass : public QObject
{
    Q_OBJECT
public:
    explicit RestApiEngineClass(QObject *parent = nullptr);
    ~RestApiEngineClass();

    void setBaseURL(QString url);
    void login(QString cardnumber, QString pin);
    void getCustomerInfo(QString cardnumber);

signals:
    void loginCorrect();
    void loginFalse(QString message);
    void customerInfoSignal(QVector<QString> info);

private slots:
    void loginSlot(QNetworkReply *reply);
    void infoSlot(QNetworkReply *reply);

private:
    QString base_url;
    QByteArray token;

    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray responseData;
};

#endif // RESTAPIENGINECLASS_H
