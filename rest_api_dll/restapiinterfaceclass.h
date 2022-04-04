#ifndef RESTAPIINTERFACECLASS_H
#define RESTAPIINTERFACECLASS_H

#include <QObject>

#include "rest_api_dll_global.h"
#include "restapiengineclass.h"

class REST_API_DLL_EXPORT RestApiInterfaceClass  : public QObject
{
    Q_OBJECT

public:
    explicit RestApiInterfaceClass(QObject *parent = nullptr);
    ~RestApiInterfaceClass();

    void setBaseURL(QString url);

    void login(QString cardnumber, QString pin);

signals:
    void loginSuccessful();
    void loginFailed();

private slots:
    void loginCorrectSlot();
    void loginFalseSlot();

private:
    RestApiEngineClass *pRestApiEngineClass;
};

#endif // RESTAPIINTERFACECLASS_H
