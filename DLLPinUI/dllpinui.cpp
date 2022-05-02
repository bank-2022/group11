#include "dllpinui.h"

DLLPinUI::DLLPinUI()
{

}

DLLPinUI::~DLLPinUI()
{

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
    pPincode->show();
}

void DLLPinUI::loginSuccessful()
{
    pPincode->loginSuccessful();
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
        connect(pCreditDebit, SIGNAL(creditDebitSignal(QString)),
                this, SLOT(creditDebitSlot(QString)),
                Qt::QueuedConnection);
        pCreditDebit->show();
    }
    else {
        emit creditDebit("debit");
        pPincode->close();
        delete pPincode;
        pPincode = nullptr;
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

void DLLPinUI::creditDebitSlot(QString choice)
{
    emit creditDebit(choice);
    delete pCreditDebit;
    pCreditDebit = nullptr;
}

