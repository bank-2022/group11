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
    pPincode->show();
    connect(pPincode, SIGNAL(sendPincode(QString)),
            this, SLOT(receivePincode(QString)),
            Qt::QueuedConnection);
}

void DLLPinUI::loginSuccessful()
{
    pPincode->loginSuccessful();
}

void DLLPinUI::loginFailed(QString message)
{
    pPincode->loginFailed(message);
}

void DLLPinUI::receivePincode(QString pin)
{
    qDebug()<<pin;
    emit sendPincode(pin);
}
