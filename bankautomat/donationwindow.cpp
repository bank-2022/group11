#include "donationwindow.h"
#include "ui_donationwindow.h"
#include "mainwindow.h"

DonationWindow::DonationWindow(QWidget *parent, MainWindow *ptr) :
    QDialog(parent), ui(new Ui::DonationWindow), pMainWindow(ptr)
{
    ui->setupUi(this);

    donationWindowTimer = new QTimer();
    donationWindowTimer->setInterval(10000);  // timer for 10 seconds
    donationWindowTimer->setSingleShot(false); // timer works more than once

    // if the timer has ran out, this window will be closed
    connect(donationWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));
}

DonationWindow::~DonationWindow()
{
    delete ui;
    ui = nullptr;

    delete donationWindowTimer;
    donationWindowTimer = nullptr;
}

void DonationWindow::startDonationWindowTimer()
{
    donationWindowTimer->start();
}

void DonationWindow::reStartDonationWindowTimer()
{
    donationWindowTimer->stop();
    donationWindowTimer->start();
}

void DonationWindow::on_exitButton_clicked()
{
    this -> close();
}

/* These functions are for different donation options (10e, 20e, 50e). */

void DonationWindow::on_tenButton_clicked()
{
    donationWindowTimer->stop();
    donationAmount="10";
    ui->amountLine->setText(donationAmount);
    donationWindowTimer->start();
}


void DonationWindow::on_twentyButton_clicked()
{
    donationWindowTimer->stop();
    donationAmount="20";
    ui->amountLine->setText(donationAmount);
    donationWindowTimer->start();
}


void DonationWindow::on_fiftyButton_clicked()
{
    donationWindowTimer->stop();
    donationAmount="50";
    ui->amountLine->setText(donationAmount);
    donationWindowTimer->start();
}


/*** These next functions are used when user wants to choose the amount manually (numbers 0-9, enter, backspace). ***/

void DonationWindow::donateOtherAmount(QString i)
{
    donationWindowTimer->stop();
    donationAmount.append(i);
    ui->amountLine->setText(donationAmount);
    donationWindowTimer->start();
}


void DonationWindow::on_oneButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("1");
    donationWindowTimer->start();
}


void DonationWindow::on_twoButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("2");
    donationWindowTimer->start();
}


void DonationWindow::on_threeButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("3");
    donationWindowTimer->start();
}


void DonationWindow::on_fourButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("4");
    donationWindowTimer->start();
}


void DonationWindow::on_fiveButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("5");
    donationWindowTimer->start();
}


void DonationWindow::on_sixButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("6");
    donationWindowTimer->start();
}


void DonationWindow::on_sevenButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("7");
    donationWindowTimer->start();
}


void DonationWindow::on_eightButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("8");
    donationWindowTimer->start();
}


void DonationWindow::on_nineButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("9");
    donationWindowTimer->start();
}


void DonationWindow::on_zeroButton_clicked()
{
    donationWindowTimer->stop();
    donateOtherAmount("0");
    donationWindowTimer->start();
}


// removes the last inserted character (aka backspace button)
void DonationWindow::on_cancelButton_clicked()
{
    donationWindowTimer->stop();
    int i = donationAmount.count();
    donationAmount.remove((i-1),1);
    ui->amountLine->setText(donationAmount);
    donationWindowTimer->start();
}


void DonationWindow::on_enterButton_clicked()
{
    donationWindowTimer->stop();
    donationWindowTimer->start();

}




