#include "dllpinui.h"

DLLPinUI::DLLPinUI()
{
    pPincode = new Pincode;
    pCreditDebit = new CreditDebit;

    connect(pPincode, SIGNAL(sendPincode(QString)),
            this, SLOT(receivePincode(QString)),
            Qt::QueuedConnection);
    connect(pPincode, SIGNAL(getType()),
            this, SLOT(getTypeSlot()),
            Qt::QueuedConnection);
    connect(pCreditDebit, SIGNAL(creditDebitSignal(QString)),
            this, SLOT(creditDebitSlot(QString)),
            Qt::QueuedConnection);
}

DLLPinUI::~DLLPinUI()
{
    delete pPincode;
    pPincode = nullptr;
    delete pCreditDebit;
    pCreditDebit = nullptr;
}

void DLLPinUI::showPincode()
{
    pPincode->show();
    pPincode->startPincodeTimer();
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
        pCreditDebit->show();
        pCreditDebit->startCreditDebitTimer();
    }
    else {
        emit creditDebit("debit");
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

void DLLPinUI::creditDebitSlot(QString choice)
{
    emit creditDebit(choice);
}

