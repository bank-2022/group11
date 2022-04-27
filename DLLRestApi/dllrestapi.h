#ifndef DLLRESTAPI_H
#define DLLRESTAPI_H

#include <QObject>
#include <QVector>

#include "DLLRestApi_global.h"
#include "dllrestapiengine.h"

/* This REST API DLL can be used by the programmers of the EXE and
 * PIN UI components of the project to make HTTP requests to the
 * REST API and interact with the database that way. All of the
 * operations start with calling a public function from this interface
 * and a signal will be emited with information as needed as a response */

class DLLRESTAPI_EXPORT DLLRestApi  : public QObject
{
    Q_OBJECT

public:
    explicit DLLRestApi(QObject *parent = nullptr);
    ~DLLRestApi();

    // It is necessary to set the base url before the use of this component
    // by calling this function with an argument like "http://localhost:3000"
    void setBaseURL(QString url);

    // This function performs a login with the arguments of a cardnumber and a pin
    // a loginSuccesfulSignal gets emited if succesful, if the login fails
    // a loginFailedSignal will be emited along with a string on the reason
    // of login failure
    void login(QString cardnumber, QString pin);

    // Performs a withdrawal from the bank account. Arguments provided = cardnumber,
    // QString amount IN CENTS! Doesn't return a signal to the main program.
    void creditWithdrawal(QString cardnumber, long long amount);
    void debitWithdrawal(QString cardnumber, long long amount);

    // These are the same as above but being charity donations the account number of the
    // charity where the donation is going is needed for the operation
    void creditDonation(QString cardnumber, QString accountnumber, long long amount);
    void debitDonation(QString cardnumber, QString accountnumber, long long amount);

    // This will update whether the card is locked (yes or no)
    void putLocked(QString cardnumber, QString locked);

    // Following functions are all GETs and will emit a signal with the information once
    // done. These are the same operations that are specified in the postman file
    // for the project
    void getLocked(QString cardnumber);
    void getType(QString cardnumber);
    void getCustomerInfo(QString cardnumber);
    void getBalance(QString accountnumber);
    void get5Transactions(QString accountnumber);
    void get10Transactions(QString accountnumber, int index); // Index is needed for 10 transactions
    // Index starts at 0 and will yield ten account transactions starting at the index number
    // with the most recents transactions first

signals:
    // These signals get emited after the login
    // and with the failed signal comes a message
    // that can be shown to the user
    void loginSuccessful();
    void loginFailed(QString message);

    // This signal gets raised if the user is trying to make unauthorized
    // REST API operations and can be used in the Main Program to lock
    // the user out of the system
    void forbiddenAccess();

    // This signal is emited when a transaction has been completed, so that the balance can be
    // updated in the main program
    void transactionComplete();

    /* These return information from the database and need to be connected to a slot
     * Customer info gets sent as a vector of 2 strings where [0] is the name and
     * [1] is account number.
     *
     * Transactions get sent as a 2 dimensional vector where the first index
     * represents the transaction and the second index is datetime, event, amount:
     * list[0][0] = transaction 1, datetime
     * list[0][1] = transaction 1, event
     * list[0][2] = transaction 1, amount (conversion and sign already made)
     * list[1][0] = transaction 2, datetime
     *
     * FOLLOWING LINES OF CODE NEED TO BE ADDED WHEN CONNECTING THESE SIGNALS TO A
     * SLOT FOR IT TO WORK (The metatypes need to be registered because of the QVectors involved):
     *
     * qRegisterMetaType<QVector<QString>>("QVector<QString");
     * qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");
     */
    void locked(QString locked);
    void type(QString type);
    void customerInfo(QVector<QString> info);
    void balance(long long balance);
    void transactions5(QVector<QVector<QString>> list);
    void transactions10(QVector<QVector<QString>> list);

private slots:
    void loginSuccessfulSlot();
    void loginFailedSlot(QString message);
    void forbiddenAccessSlot();

    void transactionCompleteSlot();

    void lockedSlot(QString sLocked);
    void typeSlot(QString sType);
    void customerInfoSlot(QVector<QString> info);
    void balanceSlot(long long llBalance);
    void transactions5Slot(QVector<QVector<QString>> list);
    void transactions10Slot(QVector<QVector<QString>> list);

private:
    DLLRestApiEngine *pDLLRestApiEngine;
};


#endif // DLLRESTAPI_H
