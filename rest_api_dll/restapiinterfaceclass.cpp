#include "restapiinterfaceclass.h"

RestApiInterfaceClass::RestApiInterfaceClass(QObject *parent)
{
    pRestApiEngineClass = new RestApiEngineClass(this);

    connect(pRestApiEngineClass, SIGNAL(loginCorrect()),
            this, SLOT(loginCorrectSlot()), Qt::QueuedConnection);

    connect(pRestApiEngineClass, SIGNAL(loginFalse(QString)),
            this, SLOT(loginFalseSlot(QString)), Qt::QueuedConnection);
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

void RestApiInterfaceClass::loginCorrectSlot()
{
    emit loginSuccessful();
}

void RestApiInterfaceClass::loginFalseSlot(QString message)
{
    emit loginFailed(message);
}
