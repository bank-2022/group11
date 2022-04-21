#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"


WithdrawWindow::WithdrawWindow(QWidget *parent, MainMenu *ptr,RestApi *api) :
    QDialog(parent),
    ui(new Ui::WithdrawWindow),
    pMainMenu(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Withdraw");

    pRestApiInterfaceClass = api;

    withdrawWindowTimer = new QTimer();
    withdrawWindowTimer->setInterval(10000); // 10 s timer
    withdrawWindowTimer->setSingleShot(false);

    withdrawWarningTimer = new QTimer();
    withdrawWarningTimer->setInterval(5000); // 5 s timer
    withdrawWarningTimer->setSingleShot(false);

    // if the 10 s timer has ran out, this window will be closed
    connect(withdrawWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));

    // if the 5 s timer has ran out, the warning will be closed
    connect(withdrawWarningTimer, SIGNAL(timeout()),
            this, SLOT(warningTimerFinished()));
}


WithdrawWindow::~WithdrawWindow()
{
    delete ui;
    delete withdrawWindowTimer;
    delete withdrawWarningTimer;
}


/* customer info functions */
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


/* timer functions */
void WithdrawWindow::startWithdrawWindowTimer()
{
    withdrawWindowTimer->start();
}

void WithdrawWindow::reStartWithdrawWindowTimer()
{
    withdrawWindowTimer->stop();
    withdrawWindowTimer->start();
}


/* functions for different withdrawal options (10e, 40e, 60e, 100e, 200e, 500e) */
void WithdrawWindow::on_tenButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="10";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fourtyButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="40";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_sixtyButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="60";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_hundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="100";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_twoHundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="200";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fiveHundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="500";
    ui->amountLine->setText(withdrawAmount);
}

/* functions for manually choosing the amount which will be withdrawn (numbers 0-9, enter, backspace) */

void WithdrawWindow::withdrawOtherAmount(QString i) // adds the chosen number at the end of the string
{
    withdrawAmount.append(i);
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_oneButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("1");
}


void WithdrawWindow::on_twoButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("2");
}


void WithdrawWindow::on_threeButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("3");
}


void WithdrawWindow::on_fourButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("4");
}


void WithdrawWindow::on_fiveButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("5");
}


void WithdrawWindow::on_sixButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("6");
}


void WithdrawWindow::on_sevenButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("7");
}


void WithdrawWindow::on_eightButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("8");
}


void WithdrawWindow::on_nineButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("9");
}


void WithdrawWindow::on_zeroButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawOtherAmount("0");
}


/* backspace button */
void WithdrawWindow::on_backspaceButton_clicked()
{
    reStartWithdrawWindowTimer();
    int i = withdrawAmount.count();
    withdrawAmount.remove((i-1),1);
    ui->amountLine->setText(withdrawAmount);
}


/* withdraw functions */
void WithdrawWindow::on_enterButton_clicked()
{
    withdrawWarningTimer->stop();
    withdrawCents = withdrawAmount.toInt() * 100;

    if (cardType == debitType){ // the user has a debit card
        qDebug("Cardtype detected");
        if (withdrawCents < 1000){ // If user tries to withdraw less than 10 €, progam will give a warning message.
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents >= 1000 && withdrawCents <= 50000){ // If the amount is big enough to be withdrawn, the program will perform the withdrawal.
            pRestApiInterfaceClass->debitWithdrawal("0987666", withdrawCents);
            withdrawCents = 0;
            withdrawAmount = "0";
            withdrawMessage("good");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents > 50000){
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
    }

    if (cardType == creditType){ // the user has a credit card

        if (withdrawCents < 1000){ // If user tries to withdraw less than 10 €, progam will give a warning message.
            withdrawMessage("bad");
        }
        else if (withdrawCents >= 1000 && withdrawCents <= 50000){ // If the amount is big enough to be withdrawn, the program will perform the withdrawal.
            pRestApiInterfaceClass->creditWithdrawal("0987666", withdrawCents);
            withdrawCents = 0;
            withdrawAmount = "0";
            withdrawMessage("good");
        }
        else if (withdrawAmount > 50000){
            withdrawMessage("bad");
        }
    }
}


void WithdrawWindow::withdrawMessage(QString message)
{
    if (message == "bad"){
        ui->amountLine->setText("Withdrawal must be between 10 - 400 €");
    }

    else if (message == "good"){
        ui->amountLine->setText("Successful withdrawal!");
    }

    else {
        ui->amountLine->setText("Unexpected error occurred!");
    }
}


void WithdrawWindow::warningTimerFinished()
{
    ui->amountLine->setText(withdrawAmount);
    withdrawWarningTimer->start();
}


void WithdrawWindow::on_exitButton_clicked()
{
    withdrawWindowTimer->stop();
    this->close();
}
