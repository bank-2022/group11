#include "restapiinterfaceclass.h"

RestApiInterfaceClass::RestApiInterfaceClass(QObject *parent)
{
    pRestApiEngineClass = new RestApiEngineClass(this);

    qRegisterMetaType<QVector<QString>>("QVector<QString");

    connect(pRestApiEngineClass, SIGNAL(loginCorrect()),
            this, SLOT(loginCorrectSlot()), Qt::QueuedConnection);

    connect(pRestApiEngineClass, SIGNAL(loginFalse(QString)),
            this, SLOT(loginFalseSlot(QString)), Qt::QueuedConnection);

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

void RestApiInterfaceClass::loginCorrectSlot()
{
    emit loginSuccessful();
}

void RestApiInterfaceClass::loginFalseSlot(QString message)
{
    emit loginFailed(message);
}

void RestApiInterfaceClass::customerInfoSlot(QVector<QString> info)
{
    emit getCustomerInfoSignal(info);
}
