#include "dllrestapi.h"

DLLRestApi::DLLRestApi(QObject *parent)
{
    pDLLRestApiEngine = new DLLRestApiEngine(this);

    // It is necessary to register the metatypes of QVectors like this if sending them in a
    // signal, otherwise it will not work
    qRegisterMetaType<QVector<QString>>("QVector<QString");
    qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");

    connect(pDLLRestApiEngine, SIGNAL(loginSuccessfulSignal()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(loginFailedSignal(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(forbiddenAccessSignal()),
            this, SLOT(forbiddenAccessSlot()), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(lockedSignal(QString)),
            this, SLOT(lockedSlot(QString)), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(typeSignal(QString)),
            this, SLOT(typeSlot(QString)), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(customerInfoSignal(QVector<QString>)),
            this, SLOT(customerInfoSlot(QVector<QString>)),
            Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(balanceSignal(long long)),
            this, SLOT(balanceSlot(long long)), Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(transactions5Signal(QVector<QVector<QString> >)),
            this, SLOT(transactions5Slot(QVector<QVector<QString> >)),
            Qt::QueuedConnection);

    connect(pDLLRestApiEngine, SIGNAL(transactions10Signal(QVector<QVector<QString> >)),
            this, SLOT(transactions10Slot(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}

DLLRestApi::~DLLRestApi()
{
    delete pDLLRestApiEngine;
    pDLLRestApiEngine = nullptr;
}

void DLLRestApi::setBaseURL(QString url)
{
    pDLLRestApiEngine->setBaseURL(url);
}

void DLLRestApi::login(QString cardnumber, QString pin)
{
    pDLLRestApiEngine->login(cardnumber, pin);
}

void DLLRestApi::creditWithdrawal(QString cardnumber, long long amount)
{
    pDLLRestApiEngine->creditWithdrawal(cardnumber, amount);
}

void DLLRestApi::debitWithdrawal(QString cardnumber, long long amount)
{
    pDLLRestApiEngine->debitWithdrawal(cardnumber, amount);
}

void DLLRestApi::creditDonation(QString cardnumber, QString accountnumber, long long amount)
{
    pDLLRestApiEngine->creditDonation(cardnumber, accountnumber, amount);
}

void DLLRestApi::debitDonation(QString cardnumber, QString accountnumber, long long amount)
{
    pDLLRestApiEngine->debitDonation(cardnumber, accountnumber, amount);
}

void DLLRestApi::putLocked(QString cardnumber, QString locked)
{
    pDLLRestApiEngine->putLocked(cardnumber, locked);
}

void DLLRestApi::getLocked(QString cardnumber)
{
    pDLLRestApiEngine->getLocked(cardnumber);
}

void DLLRestApi::getType(QString cardnumber)
{
    pDLLRestApiEngine->getType(cardnumber);
}

void DLLRestApi::getCustomerInfo(QString cardnumber)
{
    pDLLRestApiEngine->getCustomerInfo(cardnumber);
}

void DLLRestApi::getBalance(QString accountnumber)
{
    pDLLRestApiEngine->getBalance(accountnumber);
}

void DLLRestApi::get5Transactions(QString accountnumber)
{
    pDLLRestApiEngine->get5Transactions(accountnumber);
}

void DLLRestApi::get10Transactions(QString accountnumber, int index)
{
    pDLLRestApiEngine->get10Transactions(accountnumber, index);
}

void DLLRestApi::loginSuccessfulSlot()
{
    emit loginSuccessful();
}

void DLLRestApi::loginFailedSlot(QString message)
{
    emit loginFailed(message);
}

void DLLRestApi::forbiddenAccessSlot()
{
    emit forbiddenAccess();
}

void DLLRestApi::lockedSlot(QString sLocked)
{
    emit locked(sLocked);
}

void DLLRestApi::typeSlot(QString sType)
{
    emit type(sType);
}

void DLLRestApi::customerInfoSlot(QVector<QString> info)
{
    emit customerInfo(info);
}

void DLLRestApi::balanceSlot(long long llBalance)
{
    emit balance(llBalance);
}

void DLLRestApi::transactions5Slot(QVector<QVector<QString> > list)
{
    emit transactions5(list);
}

void DLLRestApi::transactions10Slot(QVector<QVector<QString> > list)
{
    emit transactions10(list);
}
