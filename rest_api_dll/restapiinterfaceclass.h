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
    void getCustomerNameAndAccountnumber(QString cardnumber);

signals:
    void loginSuccessful();
    void loginFailed(QString message);
    void customerNameAndAccountnumberSignal(QVector<QString> nameAndAccountNumber);

private slots:
    void loginCorrectSlot();
    void loginFalseSlot(QString message);
    void customerInfoSlot(QVector<QString> info);

private:
    RestApiEngineClass *pRestApiEngineClass;
};

#endif // RESTAPIINTERFACECLASS_H
