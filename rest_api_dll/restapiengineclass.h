#ifndef RESTAPIENGINECLASS_H
#define RESTAPIENGINECLASS_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

class RestApiEngineClass : public QObject
{
    Q_OBJECT
public:
    explicit RestApiEngineClass(QObject *parent = nullptr);
    ~RestApiEngineClass();

    void setBaseURL(QString url);

    void login(QString cardnumber, QString pin);

signals:
    void loginCorrect();
    void loginFalse(QString message);

private slots:
    void loginSlot(QNetworkReply *reply);

private:
    QString base_url;
    QByteArray token;

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray responseData;
};

#endif // RESTAPIENGINECLASS_H
