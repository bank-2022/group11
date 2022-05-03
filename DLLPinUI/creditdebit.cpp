#include "creditdebit.h"
#include "ui_creditdebit.h"

CreditDebit::CreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDebit)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Type Selection");
    creditDebitTimer = new QTimer();
    creditDebitTimer->setInterval(30000);
    creditDebitTimer->setSingleShot(false);

    connect(creditDebitTimer, SIGNAL(timeout()),
            this, SLOT(close()),
            Qt::QueuedConnection);
}

CreditDebit::~CreditDebit()
{
    delete ui;
    ui = nullptr;
    delete creditDebitTimer;
    creditDebitTimer = nullptr;
}

void CreditDebit::startCreditDebitTimer()
{
    creditDebitTimer->start();
}

void CreditDebit::on_CreditButton_clicked()
{
    emit creditDebitSignal("credit");
    creditDebitTimer->stop();
    this->close();
}


void CreditDebit::on_DebitButton_clicked()
{
    emit creditDebitSignal("debit");
    creditDebitTimer->stop();
    this->close();
}

