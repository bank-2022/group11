#include "restapiengine.h"

RestApiEngine::RestApiEngine(QObject *parent)
{
    // qDebug() << "EngineClass created";
}

RestApiEngine::~RestApiEngine()
{
    // qDebug() << "EngineClass destroyed";
}

void RestApiEngine::setBaseURL(QString url)
{
    base_url = url;
    // qDebug() << "Base URL set to: " << base_url;
}

void RestApiEngine::login(QString cardnumber, QString pin)
{
    QJsonObject jsonObj;

    // These are the requests body
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("pin", pin);

    // URL gets set here
    QNetworkRequest request((base_url + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // The manager gets connected to a slot that will be called when the REST API
    // operation is ready. All data will be returned from the REST API to the
    // specified slot
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)), Qt::QueuedConnection);

    // Type of HTML operation specified
    reply = manager->post(request, QJsonDocument(jsonObj).toJson());

    // All of the following functions are similar in construct
}

void RestApiEngine::creditWithdrawal(QString cardnumber, long long amount)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("amount", QString::number(amount));

    QNetworkRequest request((base_url + "/withdrawal/credit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // This is the token authorization in this and all of the following functions
    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(creditWithdrawalSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::debitWithdrawal(QString cardnumber, long long amount)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("amount", QString::number(amount));

    QNetworkRequest request((base_url + "/withdrawal/debit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(debitWithdrawalSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::creditDonation(QString cardnumber, QString accountnumber, long long amount)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("accountnumber", accountnumber);
    jsonObj.insert("amount", QString::number(amount));

    QNetworkRequest request((base_url + "/donation/credit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(creditDonationSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::debitDonation(QString cardnumber, QString accountnumber, long long amount)
{

    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("accountnumber", accountnumber);
    jsonObj.insert("amount", QString::number(amount));

    QNetworkRequest request((base_url + "/donation/debit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(debitDonationSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::putLocked(QString cardnumber, QString locked)
{
    QJsonObject jsonObj;
    jsonObj.insert("locked", locked);

    QNetworkRequest request((base_url + "/locked/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(putLockedSlot(QNetworkReply*)), Qt::QueuedConnection);

    reply = manager->put(request, QJsonDocument(jsonObj).toJson());
}

void RestApiEngine::getLocked(QString cardnumber)
{
    QNetworkRequest request((base_url + "/locked/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(lockedSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::getType(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/type/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(typeSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::getCustomerInfo(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/customer/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(customerInfoSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::getBalance(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/balance/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(balanceSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::get5Transactions(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/5transactions/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactions5Slot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::get10Transactions(QString accountnumber, int index)
{
    QNetworkRequest request((base_url + "/info/10transactions/" + accountnumber
                             + "/" + QString::number(index)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactions10Slot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void RestApiEngine::loginSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();
    // qDebug() << responseData;

    // This returns the token from the REST API
    // or an error message if login went wrong
    // and emits a signal whether the login was
    // succesful or not and why not

    if (responseData == "Wrong pin") {
        // qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Wrong pin");
    }
    else if (responseData == "Card does not exist") {
        // qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Card does not exist");
    }
    else if (responseData == "Card number or pin missing") {
        // qDebug() << "Login failed";
        token = "Bearer " + responseData;
        emit loginFailedSignal("Card number or pin missing");
    }
    else {
        // qDebug() << "Login successful";
        token = "Bearer " + responseData;
        emit loginSuccessfulSignal();
    }

    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::putLockedSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    // It is checked for each HTML operation
    // if the user is trying to access the
    // REST API services without a token
    checkForbiddenAccess(response_data);

    // Basic cleanup
    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::creditWithdrawalSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::debitWithdrawalSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::creditDonationSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::debitDonationSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    reply->deleteLater();
    manager->deleteLater();
}

void RestApiEngine::lockedSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString locked;

    locked = json_obj["locked"].toString();

    // qDebug() << locked;

    reply->deleteLater();
    manager->deleteLater();

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
    manager->deleteLater();

    emit typeSignal(type);
}

void RestApiEngine::customerInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QVector<QString> customerInfo(2);

    // This updates customers name and account number into a vector
    // of 2 strings
    customerInfo[0] = json_obj["name"].toString();
    customerInfo[1] = json_obj["accountnumber"].toString();

    reply->deleteLater();
    manager->deleteLater();

    emit customerInfoSignal(customerInfo);
}

void RestApiEngine::balanceSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    // Balance gets converted to int. Balance is in cents for accuracy
    QString balanceCents = json_obj["balance"].toString();
    long long balance = balanceCents.toLongLong();

    //qDebug() << balance;

    reply->deleteLater();
    manager->deleteLater();

    emit balanceSignal(balance);
}

void RestApiEngine::transactions5Slot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    checkForbiddenAccess(response_data);

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    // This creates a 2 dimensional vector for the transactions info

    QVector<QString> info(3);
    QVector<QVector<QString>> list(5, info);

    // Transactions get added to a 2 dimensional vector where
    // the vector contains all individual transactions
    // and the three different fields are contained in a vector inside that
    short index = 0;
    foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            list[index][0] = json_obj["datetime"].toString();
            list[index][1] = json_obj["event"].toString();
            // Cents get converted to a string of euros
            QString stringCents = json_obj["sum"].toString();
            long long sum = stringCents.toLongLong();
            QString sumString = convertToEuros(sum);
            if (list[index][1] == "withdrawal" || list[index][1] == "donation")
                list[index][2] = "- " + sumString;
            else
                list[index][2] = "+ " + sumString;
            index++;
        }

    reply->deleteLater();
    manager->deleteLater();

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

    // These operations are the same as transactions5Slot but the vector
    // size is bigger

    short index = 0;
    foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            list[index][0] = json_obj["datetime"].toString();
            list[index][1] = json_obj["event"].toString();
            QString stringCents = json_obj["sum"].toString();
            long long sum = stringCents.toLongLong();
            QString sumString = convertToEuros(sum);
            if (list[index][1] == "withdrawal" || list[index][1] == "donation")
                list[index][2] = "- " + sumString;
            else
                list[index][2] = "+ " + sumString;
            index++;
        }

    reply->deleteLater();
    manager->deleteLater();

    emit transactions10Signal(list);
}

void RestApiEngine::checkForbiddenAccess(QByteArray response_data)
{
    // This checks if the user is trying to access data unauthorized
    // and sends a signal to the main program

    if (response_data == "Forbidden" || response_data == "Unauthorized")
        emit forbiddenAccessSignal();
}

QString RestApiEngine::convertToEuros(long long sum)
{
    // This function converts a long long of cents
    // to a string of euros

    short cents = abs(sum % 100);
    QString centString;
    if (cents < 10)
        centString = "0" + QString::number(cents);
    else
        centString = QString::number(cents);

    return QString::number(sum / 100) + "." + centString;
}
