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

    void putLocked(QString cardnumber);

    void getLocked(QString cardnumber);
    void getType(QString cardnumber);
    void getCustomerInfo(QString cardnumber);
    void getBalance(QString accountnumber);
    void get5Transactions(QString accountnumber);
    void get10Transactions(QString accountnumber, int index);

signals:
    void loginSuccessfulSignal();
    void loginFailedSignal(QString message);
    void forbiddenAccessSignal();

    void lockedSignal(QString locked);
    void typeSignal(QString type);
    void customerInfoSignal(QVector<QString> info);
    void balanceSignal(QString balance);
    void transactions5Signal(QVector<QVector<QString>> list);
    void transactions10Signal(QVector<QVector<QString>> list);

private slots:
    void loginSlot(QNetworkReply *reply);

    void lockedSlot(QNetworkReply *reply);
    void typeSlot(QNetworkReply *reply);
    void customerInfoSlot(QNetworkReply *reply);
    void balanceSlot(QNetworkReply *reply);
    void transactions5Slot(QNetworkReply *reply);
    void transactions10Slot(QNetworkReply *reply);

private:
    QString base_url;
    QByteArray token;

    void checkForbiddenAccess(QByteArray response_data);

    QString convertToEuros(long long sum);
    QString convertToCents(int sum);

    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray responseData;
};

#endif // RESTAPIENGINECLASS_H
