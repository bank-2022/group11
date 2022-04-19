#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"
#include "mainwindow.h"

WithdrawWindow::WithdrawWindow(QWidget *parent, MainWindow *ptr,RestApi *api) :
    QDialog(parent), ui(new Ui::WithdrawWindow), pMainWindow(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Withdraw");

    pRestApiInterfaceClass = api;
    withdrawWindowTimer = new QTimer();
    withdrawWindowTimer->setInterval(10000);  // timer for 10 seconds
    withdrawWindowTimer->setSingleShot(false); // timer works more than once

    // if the timer has ran out, this window will be closed
    connect(withdrawWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));
}

WithdrawWindow::~WithdrawWindow()
{
    delete ui;
    delete withdrawWindowTimer;
}


void WithdrawWindow::printName(QString name)
{
    ui->nameLabel->setText(name);
}


void WithdrawWindow::printAccountNumber(QString accountNumber)
{
    ui->accountNumberLabel->setText(accountNumber);
}


void WithdrawWindow::printType(QString type)
{
    cardType = type;
    ui->typeLabel->setText(type);
}

void WithdrawWindow::printBalance(QString balance)
{
    ui->balanceLabel->setText(balance);
}


void WithdrawWindow::startWithdrawWindowTimer()
{
    withdrawWindowTimer->start();
}

void WithdrawWindow::reStartWithdrawWindowTimer()
{
    withdrawWindowTimer->stop();
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_exitButton_clicked()
{
    this->close();
}


/* These functions are for different withdrawal options (10e, 40e, 60e, 100e, 200e, 500e). */

void WithdrawWindow::on_tenButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="10";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_fourtyButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="40";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_sixtyButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="60";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_hundredButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="100";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_twoHundredButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="200";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_fiveHundredButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawAmount="500";
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}

/*** These next functions are used when user wants to choose the amount manually (numbers 0-9, enter, backspace). ***/

void WithdrawWindow::withdrawOtherAmount(QString i) // adds the chosen number at the end of the string
{
    withdrawWindowTimer->stop();
    withdrawAmount.append(i);
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_oneButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("1");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_twoButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("2");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_threeButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("3");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_fourButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("4");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_fiveButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("5");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_sixButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("6");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_sevenButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("7");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_eightButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("8");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_nineButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("9");
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_zeroButton_clicked()
{
    withdrawWindowTimer->stop();
    withdrawOtherAmount("0");
    withdrawWindowTimer->start();
}

// removes the last inserted character (aka backspace button)
void WithdrawWindow::on_backspaceButton_clicked()
{
    withdrawWindowTimer->stop();
    int i = withdrawAmount.count();
    withdrawAmount.remove((i-1),1);
    ui->amountLine->setText(withdrawAmount);
    withdrawWindowTimer->start();
}


void WithdrawWindow::on_enterButton_clicked()
{
    withdrawWindowTimer->stop();
    if (cardType == "debit"){
        ui->amountLine->setText("debit type!");

        if (withdrawAmount < 10){ // If user tries to withdraw less than 10 €, progam will give a warning message.
            ui->amountLine->setText("The withdrawable amount must be at least 10 €");
        }
        if (withdrawAmount >= 10){ // If the amount is big enough to be withdrew, the program will perform the withdrawal.
            ui->amountLine->setText("Amount OK!");
            //pRestApiInterfaceClass->debitWithdrawal(cardNumber, withdrawAmount);
        }
    }

    if (cardType == "credit"){
        ui->amountLine->setText("credit type!");
    }

    else {
        ui->amountLine->setText("ERROR, card type not found!");
    }
    // checks if the sum is under 10 € and if it is, it'll give a warning
                                // checks wether the card is debit or credit
    withdrawWindowTimer->start();
}
