#ifndef RESTAPIINTERFACECLASS_H
#define RESTAPIINTERFACECLASS_H

#include <QObject>
#include <QVector>

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

    void getCustomerInfo(QString cardnumber);

signals:
    void loginSuccessful();
    void loginFailed(QString message);
    void forbiddenAccess();

    void customerInfo(QVector<QString> info);

private slots:
    void loginSuccessfulSlot();
    void loginFailedSlot(QString message);
    void forbiddenAccessSlot();

    void customerInfoSlot(QVector<QString> info);

private:
    RestApiEngineClass *pRestApiEngineClass;
};

#endif // RESTAPIINTERFACECLASS_H
