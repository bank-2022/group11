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

void WithdrawWindow::on_oneButton_clicked()
{

}


void WithdrawWindow::on_twoButton_clicked()
{

}


void WithdrawWindow::on_threeButton_clicked()
{

}


void WithdrawWindow::on_fourButton_clicked()
{

}


void WithdrawWindow::on_fiveButton_clicked()
{

}


void WithdrawWindow::on_sixButton_clicked()
{

}


void WithdrawWindow::on_sevenButton_clicked()
{

}


void WithdrawWindow::on_eightButton_clicked()
{

}


void WithdrawWindow::on_nineButton_clicked()
{

}


void WithdrawWindow::on_zeroButton_clicked()
{

}


void WithdrawWindow::on_backspaceButton_clicked()
{

}


void WithdrawWindow::on_enterButton_clicked()
{

}

