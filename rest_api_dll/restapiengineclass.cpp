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

void RestApiEngineClass::getCustomerInfo(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/customer/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(customerInfoSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngineClass::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    qDebug() << responseData;
    if (responseData == "Wrong pin") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Wrong pin");
    }
    else if (responseData == "Card does not exist") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Card does not exist");
    }
    else if (responseData == "Card number or pin missing") {
        qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Card number or pin missing");
    }
    else {
        qDebug() << "Login successful";
        token = "Bearer " + responseData;
        emit loginSuccessfulSignal();
    }

    reply->deleteLater();
    loginManager->deleteLater();
}

void RestApiEngineClass::customerInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QVector<QString> customerInfo(2);

    customerInfo[0] = json_obj["name"].toString();
    customerInfo[1] = json_obj["accountnumber"].toString();

    reply->deleteLater();
    infoManager->deleteLater();

    emit customerInfoSignal(customerInfo);
}

void RestApiEngineClass::checkForbiddenAccess(QByteArray response_data)
{
    if (response_data == "Forbidden" || response_data == "Unauthorized")
        emit forbiddenAccessSignal();
}

