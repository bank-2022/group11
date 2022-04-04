#include "restapiengineclass.h"

RestApiEngineClass::RestApiEngineClass(QObject *parent)
{
    qDebug() << "EngineClass created";
}

RestApiEngineClass::~RestApiEngineClass()
{
    qDebug() << "EngineClass destroyed";
}

void RestApiEngineClass::setBaseURL(QString url)
{
    base_url = url;
    qDebug() << "Base URL set to: " << base_url;
}

void RestApiEngineClass::login(QString cardnumber, QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("pin", pin);

    QNetworkRequest request((base_url + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngineClass::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    qDebug() << responseData;
    if (responseData == "Wrong pin") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFalse("Wrong pin");
    }
    else if (responseData == "Card does not exist") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFalse("Card does not exist");
    }
    else if (responseData == "Card number or pin missing") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFalse("Card number or pin missing");
    }
    else {
        qDebug() << "Login successful";
        token = "Bearer " + responseData;
        emit loginCorrect();
    }
}

