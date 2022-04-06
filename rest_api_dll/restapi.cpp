#include "restapi.h"

RestApi::RestApi(QObject *parent)
{
    pRestApiEngine = new RestApiEngine(this);

    // It is necessary to register the metatypes of QVectors like this if sending them in a
    // signal, otherwise it will not work
    qRegisterMetaType<QVector<QString>>("QVector<QString");
    qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");

    connect(pRestApiEngine, SIGNAL(loginSuccessfulSignal()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(loginFailedSignal(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(forbiddenAccessSignal()),
            this, SLOT(forbiddenAccessSlot()), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(lockedSignal(QString)),
            this, SLOT(lockedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(typeSignal(QString)),
            this, SLOT(typeSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(customerInfoSignal(QVector<QString>)),
            this, SLOT(customerInfoSlot(QVector<QString>)),
            Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(balanceSignal(long long)),
            this, SLOT(balanceSlot(long long)), Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(transactions5Signal(QVector<QVector<QString> >)),
            this, SLOT(transactions5Slot(QVector<QVector<QString> >)),
            Qt::QueuedConnection);

    connect(pRestApiEngine, SIGNAL(transactions10Signal(QVector<QVector<QString> >)),
            this, SLOT(transactions10Slot(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}

RestApi::~RestApi()
{
    delete pRestApiEngine;
    pRestApiEngine = nullptr;
}

void RestApi::setBaseURL(QString url)
{
    pRestApiEngine->setBaseURL(url);
}

void RestApi::login(QString cardnumber, QString pin)
{
    pRestApiEngine->login(cardnumber, pin);
}

void RestApi::creditWithdrawal(QString cardnumber, QString amount)
{
    pRestApiEngine->creditWithdrawal(cardnumber, amount);
}

void RestApi::debitWithdrawal(QString cardnumber, QString amount)
{
    pRestApiEngine->debitWithdrawal(cardnumber, amount);
}

void RestApi::creditDonation(QString cardnumber, QString accountnumber, QString amount)
{
    pRestApiEngine->creditDonation(cardnumber, accountnumber, amount);
}

void RestApi::debitDonation(QString cardnumber, QString accountnumber, QString amount)
{
    pRestApiEngine->debitDonation(cardnumber, accountnumber, amount);
}

void RestApi::putLocked(QString cardnumber, QString locked)
{
    pRestApiEngine->putLocked(cardnumber, locked);
}

void RestApi::getLocked(QString cardnumber)
{
    pRestApiEngine->getLocked(cardnumber);
}

void RestApi::getType(QString cardnumber)
{
    pRestApiEngine->getType(cardnumber);
}

void RestApi::getCustomerInfo(QString cardnumber)
{
    pRestApiEngine->getCustomerInfo(cardnumber);
}

void RestApi::getBalance(QString accountnumber)
{
    pRestApiEngine->getBalance(accountnumber);
}

void RestApi::get5Transactions(QString accountnumber)
{
    pRestApiEngine->get5Transactions(accountnumber);
}

void RestApi::get10Transactions(QString accountnumber, int index)
{
    pRestApiEngine->get10Transactions(accountnumber, index);
}

void RestApi::loginSuccessfulSlot()
{
    emit loginSuccessful();
}

void RestApi::loginFailedSlot(QString message)
{
    emit loginFailed(message);
}

void RestApi::forbiddenAccessSlot()
{
    emit forbiddenAccess();
}

void RestApi::lockedSlot(QString sLocked)
{
    emit locked(sLocked);
}

void RestApi::typeSlot(QString sType)
{
    emit type(sType);
}

void RestApi::customerInfoSlot(QVector<QString> info)
{
    emit customerInfo(info);
}

void RestApi::balanceSlot(long long llBalance)
{
    emit balance(llBalance);
}

void RestApi::transactions5Slot(QVector<QVector<QString> > list)
{
    emit transactions5(list);
}

void RestApi::transactions10Slot(QVector<QVector<QString> > list)
{
    emit transactions10(list);
}
