#ifndef RESTAPI_H
#define RESTAPI_H

#include <QObject>
#include <QVector>

#include "rest_api_dll_global.h"
#include "restapiengine.h"

class REST_API_DLL_EXPORT RestApi  : public QObject
{
    Q_OBJECT

public:
    explicit RestApi(QObject *parent = nullptr);
    ~RestApi();

    void setBaseURL(QString url);

    void login(QString cardnumber, QString pin);

    void creditWithdrawal(QString cardnumber, int amount);
    void debitWithdrawal(QString cardnumber, int amount);
    void creditDonation(QString cardnumber, QString accountnumber, double amount);
    void debitDonation(QString cardnumber, QString accountnumber, double amount);

    void putLocked(QString cardnumber, QString locked);

    void getLocked(QString cardnumber);
    void getType(QString cardnumber);
    void getCustomerInfo(QString cardnumber);
    void getBalance(QString accountnumber);
    void get5Transactions(QString accountnumber);
    void get10Transactions(QString accountnumber, int index);

signals:
    void loginSuccessful();
    void loginFailed(QString message);
    void forbiddenAccess();

    void locked(QString locked);
    void type(QString type);
    void customerInfo(QVector<QString> info);
    void balance(QString balance);
    void transactions5(QVector<QVector<QString>> list);
    void transactions10(QVector<QVector<QString>> list);

private slots:
    void loginSuccessfulSlot();
    void loginFailedSlot(QString message);
    void forbiddenAccessSlot();

    void lockedSlot(QString sLocked);
    void typeSlot(QString sType);
    void customerInfoSlot(QVector<QString> info);
    void balanceSlot(QString sBalance);
    void transactions5Slot(QVector<QVector<QString>> list);
    void transactions10Slot(QVector<QVector<QString>> list);

private:
    RestApiEngine *pRestApiEngine;
};

#endif // RESTAPI_H
