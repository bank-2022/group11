#include "withdrawwindow.h"
#include "ui_withdrawwindow.h"
#include "mainwindow.h"

WithdrawWindow::WithdrawWindow(QWidget *parent, MainWindow *ptr) :
    QDialog(parent), ui(new Ui::WithdrawWindow), pMainWindow(ptr)
{
    ui->setupUi(this);
}

WithdrawWindow::~WithdrawWindow()
{
    delete ui;
}

void WithdrawWindow::on_exitButton_clicked()
{
    this->close();
}

/*** These functions are different withdrawal options (10e, 40e, 60e, 100e, 200e, 500e). ***/

void WithdrawWindow::on_tenButton_clicked()
{
    withdrawAmount="10";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fourtyButton_clicked()
{
    withdrawAmount="40";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_sixtyButton_clicked()
{
    withdrawAmount="60";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_hundredButton_clicked()
{
    withdrawAmount="100";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_twoHundredButton_clicked()
{
    withdrawAmount="200";
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_fiveHundredButton_clicked()
{
    withdrawAmount="500";
    ui->amountLine->setText(withdrawAmount);
}

/*** These next functions are used when user wants to choose the amount manually (numbers 0-9, enter, backspace). ***/

void WithdrawWindow::withdrawOtherAmount(QString i) // adds the chosen number at the end of the string
{
    withdrawAmount.append(i);
    ui->amountLine->setText(withdrawAmount);
}

void WithdrawWindow::on_oneButton_clicked()
{
    withdrawOtherAmount("1");
}


void WithdrawWindow::on_twoButton_clicked()
{
    withdrawOtherAmount("2");
}


void WithdrawWindow::on_threeButton_clicked()
{
    withdrawOtherAmount("3");
}


void WithdrawWindow::on_fourButton_clicked()
{
    withdrawOtherAmount("4");
}


void WithdrawWindow::on_fiveButton_clicked()
{
    withdrawOtherAmount("5");
}


void WithdrawWindow::on_sixButton_clicked()
{
    withdrawOtherAmount("6");
}


void WithdrawWindow::on_sevenButton_clicked()
{
    withdrawOtherAmount("7");
}


void WithdrawWindow::on_eightButton_clicked()
{
    withdrawOtherAmount("8");
}


void WithdrawWindow::on_nineButton_clicked()
{
    withdrawOtherAmount("9");
}


void WithdrawWindow::on_zeroButton_clicked()
{
    withdrawOtherAmount("0");
}

// removes the last inserted character (aka backspace button)
void WithdrawWindow::on_backspaceButton_clicked()
{
    int i = withdrawAmount.count();
    withdrawAmount.remove((i-1),1);
    ui->amountLine->setText(withdrawAmount);
}


void WithdrawWindow::on_enterButton_clicked()
{
//tänne pitäisi luoda systeemi, joka tarkistaa että valittu summa ei oo alle 10€ ja laittaa varotuksen jos on
}



