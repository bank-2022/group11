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
