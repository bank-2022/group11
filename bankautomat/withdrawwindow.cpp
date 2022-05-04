#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"

#include "mainwindow.h"


/* In this window the user will be able to withdraw money from their account. The
 * user can also view their account information (name, balance and accountnumber).*/


WithdrawWindow::WithdrawWindow(QWidget *parent, MainMenu *ptr, DLLRestApi *api) :
    QDialog(parent),
    ui(new Ui::WithdrawWindow),
    pMainMenu(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Withdraw");

    pRestApi = api;

    withdrawWindowTimer = new QTimer();
    withdrawWindowTimer->setInterval(10000); // 10 s timer
    withdrawWindowTimer->setSingleShot(false);

    withdrawWarningTimer = new QTimer();
    withdrawWarningTimer->setInterval(5000); // 5 s timer
    withdrawWarningTimer->setSingleShot(false);

    // if the 10 s timer has ran out, this window will be closed
    connect(withdrawWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()), Qt::QueuedConnection);

    // if the 5 s timer has ran out, the warning will be closed
    connect(withdrawWarningTimer, SIGNAL(timeout()),
            this, SLOT(warningTimerFinished()), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(transactionComplete()),
            this, SLOT(getBalance()), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);
}


WithdrawWindow::~WithdrawWindow()
{
    delete ui;
    ui = nullptr;

    delete withdrawWindowTimer;
    withdrawWindowTimer = nullptr;

    delete withdrawWarningTimer;
    withdrawWarningTimer = nullptr;
}


/* customer info functions */
void WithdrawWindow::printName(QString name)
{
    ui->nameLabel->setText("Name: "+name);
}


void WithdrawWindow::printAccountNumber(QString accountNumber)
{
    accountNum = accountNumber;
    ui->accountNumberLabel->setText("Account: "+accountNumber);
}


void WithdrawWindow::printType(QString type)
{
    cardType = type;
    ui->typeLabel->setText(type);
}

void WithdrawWindow::printBalance(QString balance)
{
    stringBalance = balance;
    ui->balanceLabel->setText("Balance: "+balance+" €");
}


void WithdrawWindow::getCardNumber(QString cardnumber)
{
    cardNumber = cardnumber;
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


void WithdrawWindow::warningTimerFinished()
{
    withdrawWarningTimer->stop();
    withdrawAmount="0";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


/* functions for different withdrawal options (10e, 40e, 60e, 100e, 200e, 500e) */
void WithdrawWindow::on_tenButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="10";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fourtyButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="40";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_sixtyButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="60";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_hundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="100";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_twoHundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="200";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fiveHundredButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="500";
    withdrawFlag = true;
    ui->amountLine->setText(withdrawAmount);
}

/* functions for manually choosing the amount which will be withdrawn (numbers 0-9, enter, backspace) */

void WithdrawWindow::withdrawOtherAmount(QString i) // adds the chosen number at the end of the string
{
    if (withdrawFlag == true) {
        withdrawAmount = i;
        ui->amountLine->clear();
        ui->amountLine->setText(withdrawAmount);
        withdrawFlag = false;
    }
    else if (withdrawFlag == false) {
        withdrawAmount.append(i);
        ui->amountLine->setText(withdrawAmount);
    }
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
void WithdrawWindow::on_clearButton_clicked()
{
    reStartWithdrawWindowTimer();
    withdrawAmount="0";
    withdrawFlag = true;
    ui->amountLine->clear();
}


/* withdraw functions */
void WithdrawWindow::on_enterButton_clicked()
{
    withdrawWarningTimer->stop();

    withdrawCents = withdrawAmount.toInt() * 100;
    double remainder = withdrawCents % 1000;
    longCentsBalance = stringBalance.toDouble() * 100;

    double creditLimit = -500000; // credit limit is 5000 €

    /* debit card */
    if (cardType == debitType){

        if (withdrawCents < 1000){ // user tries to withdraw less than 10 €
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents > 50000){ // user tries to withdraw more than 500 €
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents >= 1000 && withdrawCents <= 50000){ // the amount is 10 - 500 €

            if (remainder != 0){ // the amount is not divisible by ten
                withdrawMessage("false");
                withdrawWarningTimer->start();
            }

            else if (remainder == 0){ // the amount is divisible by ten

                if (longCentsBalance >= withdrawCents){ // user has enough money (and is using a debit card)
                    pRestApi->debitWithdrawal(cardNumber, withdrawCents);
                    withdrawCents = 0;
                    withdrawAmount = "0";
                    withdrawMessage("good");
                    withdrawWarningTimer->start();
                }

                else if (longCentsBalance < withdrawCents){ // the balance isn't enough
                    withdrawMessage("poor");
                    withdrawWarningTimer->start();
                }
            }

        }
    }

    /* credit card */
    if (cardType == creditType){

        if (withdrawCents < 1000){ // user tries to withdraw less than 10 €
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents > 50000){ // user tries to withdraw more than 500 €
            withdrawMessage("bad");
            withdrawWarningTimer->start();
        }
        else if (withdrawCents >= 1000 && withdrawCents <= 50000){ // the amount is 10 - 500 €

            if (remainder != 0){ // the amount is not divisible by ten
                withdrawMessage("false");
                withdrawWarningTimer->start();
            }

            else if (remainder == 0){ // the amount is divisible by ten

                if (longCentsBalance >= creditLimit){ // user has not exeeded the credit limit (and is using a credit card)
                    pRestApi->creditWithdrawal(cardNumber, withdrawCents);
                    withdrawCents = 0;
                    withdrawAmount = "0";
                    withdrawMessage("good");
                    withdrawWarningTimer->start();
                }

                else if (longCentsBalance <= creditLimit){ // the credit limit has been exeeded
                    withdrawMessage("poor");
                    withdrawWarningTimer->start();
                }
            }
        }
    }
}


void WithdrawWindow::withdrawMessage(QString message)
{
    if (message == "bad"){
        ui->amountLine->setText("Withdrawal must be between 10 - 500 €");
    }

    else if (message == "good"){
        ui->amountLine->setText("Successful withdrawal!");
    }

    else if (message == "poor"){
        ui->amountLine->setText("Not enough money on account!");
    }

    else if (message == "false"){
        ui->amountLine->setText("Amount must be divisible by ten.");
    }

    else {
        ui->amountLine->setText("Unexpected error occurred!");
    }
}


void WithdrawWindow::getBalance()
{
    pRestApi->getBalance(accountNum);
}


void WithdrawWindow::updateBalance(long long balance)
{
    QString stringBalance = convertToEuros(balance);
    ui->balanceLabel->setText(stringBalance);
}


QString WithdrawWindow::convertToEuros(long long sum)
{
    // This function converts a long long of cents
    // to a string of euros

    int cents = abs(sum % 100);
    QString centString;
    if (cents < 10)
    {
        centString = "0" + QString::number(cents);
    }
    else
    {
        centString = QString::number(cents);
    }
    return QString::number(sum / 100) + "." + centString;
}


void WithdrawWindow::on_exitButton_clicked()
{
    /* stops the withdraw window timer,
     * clears withdraw amount and amount line
     * starts the main menu timer
     * and closes the withdraw window */

    withdrawWindowTimer->stop();
    withdrawAmount="0";
    withdrawFlag = true;
    ui->amountLine->clear();
    pMainMenu->startMainMenuTimer();
    this->close();
}


void WithdrawWindow::clearWithdrawWindow()
{
    ui->amountLine->clear();
    ui->accountNumberLabel->clear();
    ui->balanceLabel->clear();
    ui->nameLabel->clear();
    ui->typeLabel->clear();
    this->close();
}
