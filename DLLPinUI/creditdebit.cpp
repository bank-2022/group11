#include "creditdebit.h"
#include "ui_creditdebit.h"

CreditDebit::CreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDebit)
{
    ui->setupUi(this);
}

CreditDebit::~CreditDebit()
{
    delete ui;
}

void CreditDebit::on_CreditButton_clicked()
{
    emit creditDebitSignal("credit");
    this->close();
}


void CreditDebit::on_DebitButton_clicked()
{
    emit creditDebitSignal("debit");
    this->close();
}

