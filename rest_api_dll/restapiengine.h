#ifndef RESTAPIENGINE_H
#define RESTAPIENGINE_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QVector>

class RestApiEngine : public QObject
{
    Q_OBJECT
public:
    explicit RestApiEngine(QObject *parent = nullptr);
    ~RestApiEngine();

    void setBaseURL(QString url);

    void login(QString cardnumber, QString pin);

    void creditWithdrawal(QString cardnumber, QString amount);
    void debitWithdrawal(QString cardnumber, QString amount);
    void creditDonation(QString cardnumber, QString accountnumber, QString amount);
    void debitDonation(QString cardnumber, QString accountnumber, QString amount);

    void putLocked(QString cardnumber, QString locked);

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
    void balanceSignal(int balance);
    void transactions5Signal(QVector<QVector<QString>> list);
    void transactions10Signal(QVector<QVector<QString>> list);

private slots:
    void loginSlot(QNetworkReply *reply);

    void putLockedSlot(QNetworkReply *reply);

    void creditWithdrawalSlot(QNetworkReply *reply);
    void debitWithdrawalSlot(QNetworkReply *reply);
    void creditDonationSlot(QNetworkReply *reply);
    void debitDonationSlot(QNetworkReply *reply);

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

    QString convertToEuros(int sum);

    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray responseData;
};

#endif // RESTAPIENGINE_H
