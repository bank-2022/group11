#ifndef INTERFACECLASS_H
#define INTERFACECLASS_H

#include <QObject>

#include "rest_api_dll_global.h"
#include "engineclass.h"

class REST_API_DLL_EXPORT InterfaceClass  : public QObject
{
    Q_OBJECT

public:
    explicit InterfaceClass(QObject *parent = nullptr);

private:
    EngineClass *pEngineClass;
};

#endif // INTERFACECLASS_H
