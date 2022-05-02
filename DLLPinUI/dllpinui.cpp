#include "dllpinui.h"

DLLPinUI::DLLPinUI()
{

}

DLLPinUI::~DLLPinUI()
{
    delete pPincode;
    pPincode = nullptr;
}

void DLLPinUI::showPincode()
{
    pPincode = new Pincode;
    connect(pPincode, SIGNAL(sendPincode(QString)),
            this, SLOT(receivePincode(QString)),
            Qt::QueuedConnection);
    connect(pPincode, SIGNAL(getType()),
            this, SLOT(getTypeSlot()),
            Qt::QueuedConnection);
    connect(pPincode, SIGNAL(putLocked(QString)),
            this, SLOT(putLockedSlot(QString)),
            Qt::QueuedConnection);
    pPincode->show();
}

void DLLPinUI::loginSuccessful(bool locked)
{
    pPincode->loginSuccessful(locked);
}

void DLLPinUI::loginFailed(QString message)
{
    pPincode->loginFailed(message);
}

void DLLPinUI::showCreditDebit(QString type)
{
    if (type == "credit") {
        pPincode->close();
        pCreditDebit = new CreditDebit;
        pCreditDebit->show();
    }
    else {
        pPincode->close();
    }
}

void DLLPinUI::receivePincode(QString pin)
{
    emit sendPincode(pin);
}

void DLLPinUI::getTypeSlot()
{
    emit getType();
}

void DLLPinUI::putLockedSlot(QString locked)
{
    emit putLocked(locked);
}
