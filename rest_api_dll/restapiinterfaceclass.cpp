#include "restapiinterfaceclass.h"

RestApiInterfaceClass::RestApiInterfaceClass(QObject *parent)
{
    pRestApiEngineClass = new RestApiEngineClass(this);

    qRegisterMetaType<QVector<QString>>("QVector<QString");

    connect(pRestApiEngineClass, SIGNAL(loginSuccessfulSignal()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pRestApiEngineClass, SIGNAL(loginFailedSignal(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiEngineClass, SIGNAL(forbiddenAccessSignal()),
            this, SLOT(forbiddenAccessSlot()), Qt::QueuedConnection);

    connect(pRestApiEngineClass, SIGNAL(customerInfoSignal(QVector<QString>)),
            this, SLOT(customerInfoSlot(QVector<QString>)),
            Qt::QueuedConnection);
}

RestApiInterfaceClass::~RestApiInterfaceClass()
{
    delete pRestApiEngineClass;
    pRestApiEngineClass = nullptr;
}

void RestApiInterfaceClass::setBaseURL(QString url)
{
    pRestApiEngineClass->setBaseURL(url);
}

void RestApiInterfaceClass::login(QString cardnumber, QString pin)
{
    pRestApiEngineClass->login(cardnumber, pin);
}

void RestApiInterfaceClass::getCustomerInfo(QString cardnumber)
{
    pRestApiEngineClass->getCustomerInfo(cardnumber);
}

void RestApiInterfaceClass::loginSuccessfulSlot()
{
    emit loginSuccessful();
}

void RestApiInterfaceClass::loginFailedSlot(QString message)
{
    emit loginFailed(message);
}

void RestApiInterfaceClass::forbiddenAccessSlot()
{
    emit forbiddenAccess();
}

void RestApiInterfaceClass::customerInfoSlot(QVector<QString> info)
{
    emit customerInfo(info);
}
