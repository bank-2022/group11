#include "restapiengineclass.h"

RestApiEngineClass::RestApiEngineClass(QObject *parent)
{
    qDebug() << "EngineClass created";
}

RestApiEngineClass::~RestApiEngineClass()
{
    qDebug() << "EngineClass destroyed";
}

void RestApiEngineClass::setSiteURL(QString url)
{
    site_url = url;
    qDebug() << "Site URL set to: " << site_url;
}

QString RestApiEngineClass::login()
{

}
