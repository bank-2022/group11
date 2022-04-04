#include "restapiinterfaceclass.h"

RestApiInterfaceClass::RestApiInterfaceClass(QObject *parent)
{
    pRestApiEngineClass = new RestApiEngineClass(this);
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
