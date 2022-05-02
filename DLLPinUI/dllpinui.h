#ifndef DLLPINUI_H
#define DLLPINUI_H

#include "DLLPinUI_global.h"
#include <QObject>
#include "creditdebit.h"
#include "pincode.h"
#include <QStackedWidget>
#include <QVBoxLayout>

class DLLPINUI_EXPORT DLLPinUI : public QObject
{
    Q_OBJECT

public:
    DLLPinUI();
    ~DLLPinUI();
    void showPincode();
    void loginSuccessful(bool locked);
    void loginFailed(QString message);
    void showCreditDebit(QString type);

signals:
    void sendPincode(QString pin);
    void getType();
    void putLocked(QString locked);

private slots:
    void receivePincode(QString pin);
    void getTypeSlot();
    void putLockedSlot(QString locked);

private:
    Pincode * pPincode;
    CreditDebit * pCreditDebit;
    QStackedWidget * pStackedWidget;
    QVBoxLayout * pLayout;

};

#endif // DLLPINUI_H
