#ifndef DLLPINUI_H
#define DLLPINUI_H

#include "DLLPinUI_global.h"
#include <QObject>
#include "creditdebit.h"
#include "pincode.h"

class DLLPINUI_EXPORT DLLPinUI : public QObject
{
    Q_OBJECT

public:
    DLLPinUI();
    ~DLLPinUI();
    void showPincode();
    void loginSuccessful();
    void loginFailed(QString message);

signals:
    void sendPincode(QString pin);

private slots:
    void receivePincode(QString pin);

private:
    Pincode * pPincode;
    CreditDebit * pCreditDebit;

};

#endif // DLLPINUI_H
