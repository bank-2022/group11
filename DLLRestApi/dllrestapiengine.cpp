#include "dllrestapiengine.h"

DLLRestApiEngine::DLLRestApiEngine(QObject *parent)
{
    // qDebug() << "EngineClass created";
}

DLLRestApiEngine::~DLLRestApiEngine()
{
    // qDebug() << "EngineClass destroyed";
}

void DLLRestApiEngine::setBaseURL(QString url)
{
    base_url = url;
    // qDebug() << "Base URL set to: " << base_url;
}

void DLLRestApiEngine::login(QString cardnumber, QString pin)
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

void DLLRestApiEngine::creditWithdrawal(QString cardnumber, long long amount)
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

void DLLRestApiEngine::debitWithdrawal(QString cardnumber, long long amount)
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

void DLLRestApiEngine::creditDonation(QString cardnumber, QString accountnumber, long long amount)
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

void DLLRestApiEngine::debitDonation(QString cardnumber, QString accountnumber, long long amount)
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

void DLLRestApiEngine::putLocked(QString cardnumber, QString locked)
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

void DLLRestApiEngine::getLocked(QString cardnumber)
{
    QNetworkRequest request((base_url + "/locked/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(lockedSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void DLLRestApiEngine::getType(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/type/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(typeSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void DLLRestApiEngine::getCustomerInfo(QString cardnumber)
{
    QNetworkRequest request((base_url + "/info/customer/" + cardnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(customerInfoSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void DLLRestApiEngine::getBalance(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/balance/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(balanceSlot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void DLLRestApiEngine::get5Transactions(QString accountnumber)
{
    QNetworkRequest request((base_url + "/info/5transactions/" + accountnumber));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(token));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(transactions5Slot(QNetworkReply*)), Qt::QueuedConnection);
    reply = manager->get(request);
}

void DLLRestApiEngine::get10Transactions(QString accountnumber, int index)
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

void DLLRestApiEngine::loginSlot(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        emit loginFailedSignal("Error connecting to server");
    else {
        responseData = reply->readAll();
        // qDebug() << responseData;

        // This returns the token from the REST API
        // or an error message if login went wrong
        // and emits a signal whether the login was
        // succesful or not and why not

        if (responseData == "Database error") {
            // qDebug() << "Login failed";
            token = "Bearer ";
            emit loginFailedSignal(responseData);
        }
        else if (responseData == "Wrong pin") {
            // qDebug() << "Login failed";
            token = "Bearer ";
            emit loginFailedSignal(responseData);
        }
        else if (responseData == "Card does not exist") {
            // qDebug() << "Login failed";
            token = "Bearer ";
            emit loginFailedSignal(responseData);
        }
        else if (responseData == "Card number or pin missing") {
            // qDebug() << "Login failed";
            token = "Bearer ";
            emit loginFailedSignal(responseData);
        }
        else {
            // qDebug() << "Login successful";
            token = "Bearer " + responseData;
            emit loginSuccessfulSignal();
        }
    }

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::putLockedSlot(QNetworkReply *reply)
{
    errorHandling(reply);

    // Basic cleanup
    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::creditWithdrawalSlot(QNetworkReply *reply)
{
    if(errorHandling(reply))
        emit transactionCompleteSignal();

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();


}

void DLLRestApiEngine::debitWithdrawalSlot(QNetworkReply *reply)
{
    if(errorHandling(reply))
        emit transactionCompleteSignal();

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::creditDonationSlot(QNetworkReply *reply)
{
    if(errorHandling(reply))
        emit transactionCompleteSignal();

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::debitDonationSlot(QNetworkReply *reply)
{
    if(errorHandling(reply))
        emit transactionCompleteSignal();

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::lockedSlot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        QString locked;

        locked = json_obj["locked"].toString();

        emit lockedSignal(locked);
    }

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::typeSlot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        QString type;

        type = json_obj["type"].toString();

        emit typeSignal(type);
    }

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::customerInfoSlot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        QVector<QString> customerInfo(2);

        // This updates customers name and account number into a vector
        // of 2 strings
        customerInfo[0] = json_obj["name"].toString();
        customerInfo[1] = json_obj["accountnumber"].toString();

        emit customerInfoSignal(customerInfo);
    }


    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::balanceSlot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        // Balance gets converted to int. Balance is in cents for accuracy
        QString balanceCents = json_obj["balance"].toString();
        long long balance = balanceCents.toLongLong();

        emit balanceSignal(balance);
    }


    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::transactions5Slot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

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

        emit transactions5Signal(list);
    }

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void DLLRestApiEngine::transactions10Slot(QNetworkReply *reply)
{
    if(errorHandling(reply)) {
        QByteArray response_data=reply->readAll();

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

        emit transactions10Signal(list);
    }

    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();  
}

QString DLLRestApiEngine::convertToEuros(long long sum)
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

bool DLLRestApiEngine::errorHandling(QNetworkReply *reply)
{
    QNetworkReply::NetworkError errorType = reply->error();
    if (errorType == QNetworkReply::ContentAccessDenied ||
        errorType == QNetworkReply::ContentOperationNotPermittedError ||
        errorType == QNetworkReply::AuthenticationRequiredError) {
        emit forbiddenAccessSignal();
        return false;
    }
    else if (errorType != QNetworkReply::NoError) {
        emit errorSignal();
        return false;
    }
    else
        return true;
}
