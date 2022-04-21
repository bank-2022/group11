#include "donationwindow.h"
#include "ui_donationwindow.h"


DonationWindow::DonationWindow(QWidget *parent, MainMenu *ptr, RestApi *api) :
    QDialog(parent),
    ui(new Ui::DonationWindow),
    pMainMenu(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Donate");

    pRestApiInterfaceClass = api;

    donationWindowTimer = new QTimer();
    donationWindowTimer->setInterval(10000);  // 10 s timer
    donationWindowTimer->setSingleShot(false);

    // if the 10 s timer has ran out, this window will be closed
    connect(donationWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));
}

DonationWindow::~DonationWindow()
{
    delete ui;
    delete donationWindowTimer;
}


/* customer info functions */
void DonationWindow::printName(QString name)
{
    ui->nameLabel->setText(name);
}


void DonationWindow::printAccountNumber(QString accountNumber)
{
    ui->accountNumberLabel->setText(accountNumber);
}


void DonationWindow::printType(QString type)
{
    cardType = type;
    ui->typeLabel->setText(type);
}


void DonationWindow::printBalance(QString balance)
{
    ui->balanceLabel->setText(balance);
}


/* timer functions */
void DonationWindow::startDonationWindowTimer()
{
    donationWindowTimer->start();
}

void DonationWindow::reStartDonationWindowTimer()
{
    donationWindowTimer->stop();
    donationWindowTimer->start();
}


/* functions for different donation options (10e, 20e, 50e). */
void DonationWindow::on_tenButton_clicked()
{
    reStartDonationWindowTimer();
    donationAmount="10";
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_twentyButton_clicked()
{
    reStartDonationWindowTimer();
    donationAmount="20";
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_fiftyButton_clicked()
{
    reStartDonationWindowTimer();
    donationAmount="50";
    ui->amountLine->setText(donationAmount);
}


/* functions for manually choosing the amount which will be donated (numbers 0-9, enter, backspace) */

void DonationWindow::donateOtherAmount(QString i)
{
    reStartDonationWindowTimer();
    donationAmount.append(i);
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_oneButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("1");
}


void DonationWindow::on_twoButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("2");
}


void DonationWindow::on_threeButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("3");
}


void DonationWindow::on_fourButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("4");
}


void DonationWindow::on_fiveButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("5");
}


void DonationWindow::on_sixButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("6");
}


void DonationWindow::on_sevenButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("7");
}


void DonationWindow::on_eightButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("8");
}


void DonationWindow::on_nineButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("9");
}


void DonationWindow::on_zeroButton_clicked()
{
    reStartDonationWindowTimer();
    donateOtherAmount("0");
}


/* backspace button */
void DonationWindow::on_cancelButton_clicked()
{
    reStartDonationWindowTimer();
    int i = donationAmount.count();
    donationAmount.remove((i-1),1);
    ui->amountLine->setText(donationAmount);
}


/* donation functions */
void DonationWindow::on_enterButton_clicked()
{
    reStartDonationWindowTimer();

    if (cardType == debitType){ // the user has a debit card
        if (donationAmount < 10){ // If user tries to withdraw less than 10 €, progam will give a warning message.
            donateMessage("bad");
        }
        else if (donationAmount >= 10 && donationAmount <= 1000){ // If the amount is big enough to be withdrawn, the program will perform the withdrawal.
            donationCents = donationAmount.toInt() * 100;
            pRestApiInterfaceClass->debitDonation("0987666", charityAccount, donationCents); // doesn't work yet
            donateMessage("good");
        }
        else if (donationAmount > 1000){
            donateMessage("bad");
        }
    }

    if (cardType == creditType){ // the user has a credit card
        if (donationAmount < 10){ // If user tries to withdraw less than 10 €, progam will give a warning message.
            donateMessage("bad");
        }
        if (donationAmount >= 10 && donationAmount <= 1000){ // If the amount is big enough to be withdrawn, the program will perform the withdrawal.
            donationCents = donationAmount.toInt() * 100;
            pRestApiInterfaceClass->creditDonation("0987666", charityAccount, 1000);
            donateMessage("good");
        }
        if (donationAmount > 1000){
            donateMessage("bad");
        }
    }
}


void DonationWindow::donateMessage(QString message)
{
    if (message == "bad"){
        ui->amountLine->setText("Donation must be between 10 - 400 €");
    }

    else if (message == "good"){
        ui->amountLine->setText("Successful donation!");
    }

    else {
        ui->amountLine->setText("ERROR!");
    }
}


void DonationWindow::on_exitButton_clicked()
{
    donationWindowTimer->stop();
    this -> close();
}
