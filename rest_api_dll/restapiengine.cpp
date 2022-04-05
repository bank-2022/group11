#include "restapiengine.h"

RestApiEngine::RestApiEngine(QObject *parent)
{
    qDebug() << "EngineClass created";
}

RestApiEngine::~RestApiEngine()
{
    qDebug() << "EngineClass destroyed";
}

void RestApiEngine::setBaseURL(QString url)
{
    base_url = url;
    qDebug() << "Base URL set to: " << base_url;
}

void RestApiEngine::login(QString cardnumber, QString pin)
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

void RestApiEngine::creditWithdrawal(QString cardnumber, int amount)
{

}

void RestApiEngine::debitWithdrawal(QString cardnumber, int amount)
{

}

void RestApiEngine::creditDonation(QString cardnumber, QString accountnumber, double amount)
{

}

void RestApiEngine::debitDonation(QString cardnumber, QString accountnumber, double amount)
{

}

void RestApiEngine::putLocked(QString cardnumber, QString locked)
{
    QJsonObject jsonObj;
    jsonObj.insert("locked", locked);

    QNetworkRequest request((base_url + "/locked/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(putLockedSlot(QNetworkReply*)));

    reply = infoManager->put(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::getLocked(QString cardnumber)
{
    QNetworkRequest request((base_url + "/locked/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(lockedSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::getType(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/type/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(typeSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::getCustomerInfo(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/customer/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(customerInfoSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::getBalance(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/balance/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(balanceSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::get5Transactions(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/5transactions/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactions5Slot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::get10Transactions(QString accountnumber, int index)
{
    QNetworkRequest request((base_url + "/info/10transactions/" + accountnumber
                             + "/" + QString::number(index)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    infoManager = new QNetworkAccessManager(this);
    connect(infoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactions10Slot(QNetworkReply*)), Qt::QueuedConnection);
    reply = infoManager->get(request);
}

void RestApiEngine::loginSlot(QNetworkReply *reply)
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

void RestApiEngine::putLockedSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    reply->deleteLater();
    infoManager->deleteLater();
}

void RestApiEngine::lockedSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString locked;

    locked = json_obj["locked"].toString();

    qDebug() << locked;

    reply->deleteLater();
    infoManager->deleteLater();

    emit lockedSignal(locked);
}

void RestApiEngine::typeSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString type;

    type = json_obj["type"].toString();

    reply->deleteLater();
    infoManager->deleteLater();

    emit typeSignal(type);
}

void RestApiEngine::customerInfoSlot(QNetworkReply *reply)
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

void RestApiEngine::balanceSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    int balance;

    balance = (long long)json_obj["balance"].toDouble();

    QString balanceString = convertToEuros(balance);

    reply->deleteLater();
    infoManager->deleteLater();

    emit typeSignal(balanceString);
}

void RestApiEngine::transactions5Slot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QVector<QString> info(3);
    QVector<QVector<QString>> list(5, info);

    short index = 0;
    foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            list[index][0] = json_obj["datetime"].toString();
            list[index][1] = json_obj["event"].toString();
            int sum = json_obj["sum"].toInt();
            QString sumString = convertToEuros(sum);
            if (list[index][1] == "withdrawal" || list[index][1] == "donation")
                list[index][2] = "- " + sumString;
            else
                list[index][2] = "+ " + sumString;
            index++;
        }

    reply->deleteLater();
    infoManager->deleteLater();

    emit transactions5Signal(list);
}

void RestApiEngine::transactions10Slot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QVector<QString> info(3);
    QVector<QVector<QString>> list(10, info);

    short index = 0;
    foreach (const QJsonValue &value, json_array) {
            qDebug() << "here";
            QJsonObject json_obj = value.toObject();
            list[index][0] = json_obj["datetime"].toString();
            list[index][1] = json_obj["event"].toString();
            int sum = json_obj["sum"].toInt();
            QString sumString = convertToEuros(sum);
            if (list[index][1] == "withdrawal" || list[index][1] == "donation")
                list[index][2] = "- " + sumString;
            else
                list[index][2] = "+ " + sumString;
            index++;
        }

    reply->deleteLater();
    infoManager->deleteLater();

    emit transactions10Signal(list);
}

void RestApiEngine::checkForbiddenAccess(QByteArray response_data)
{
    if (response_data == "Forbidden" || response_data == "Unauthorized")
        emit forbiddenAccessSignal();
}

QString RestApiEngine::convertToEuros(long long sum)
{
    long long cents = sum % 100;
    QString centString;
    if (cents < 10)
        centString = "0" + QString::number(cents);
    else
        centString = QString::number(cents);

    return QString::number(sum / 100) + "." + centString;
}

QString RestApiEngine::convertToCents(int sum)
{
    return QString::number(sum * 100);
}

