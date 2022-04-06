#include "donationwindow.h"
#include "ui_donationwindow.h"
#include "mainwindow.h"

DonationWindow::DonationWindow(QWidget *parent, MainWindow *ptr) :
    QDialog(parent), ui(new Ui::DonationWindow), pMainWindow(ptr)
{
    ui->setupUi(this);
}

DonationWindow::~DonationWindow()
{
    delete ui;
}

/*** These functions are different donation options (10e, 20e, 50e). ***/

void DonationWindow::on_tenButton_clicked()
{
    donationAmount="10";
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_twentyButton_clicked()
{
    donationAmount="20";
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_fiftyButton_clicked()
{
    donationAmount="50";
    ui->amountLine->setText(donationAmount);
}


/*** These next functions are used when user wants to choose the amount manually (numbers 0-9, enter, backspace). ***/

void DonationWindow::donateOtherAmount(QString i)
{
    donationAmount.append(i);
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_oneButton_clicked()
{
    donateOtherAmount("1");
}


void DonationWindow::on_twoButton_clicked()
{
    donateOtherAmount("2");
}


void DonationWindow::on_threeButton_clicked()
{
    donateOtherAmount("3");
}


void DonationWindow::on_fourButton_clicked()
{
    donateOtherAmount("4");
}


void DonationWindow::on_fiveButton_clicked()
{
    donateOtherAmount("5");
}


void DonationWindow::on_sixButton_clicked()
{
    donateOtherAmount("6");
}


void DonationWindow::on_sevenButton_clicked()
{
    donateOtherAmount("7");
}


void DonationWindow::on_eightButton_clicked()
{
    donateOtherAmount("8");
}


void DonationWindow::on_nineButton_clicked()
{
    donateOtherAmount("9");
}


void DonationWindow::on_zeroButton_clicked()
{
    donateOtherAmount("0");
}


// removes the last inserted character (aka backspace button)
void DonationWindow::on_cancelButton_clicked()
{
    int i = donationAmount.count();
    donationAmount.remove((i-1),1);
    ui->amountLine->setText(donationAmount);
}


void DonationWindow::on_enterButton_clicked()
{

}


void DonationWindow::on_exitButton_clicked()
{
    this -> close();
}

