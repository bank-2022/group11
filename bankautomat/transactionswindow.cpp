#include "transactionswindow.h"
#include "ui_transactionswindow.h"
#include "mainwindow.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
}

void TransactionsWindow::on_nextButton_clicked()
{

}


void TransactionsWindow::on_previousButton_clicked()
{

}


void TransactionsWindow::on_exitButton_clicked()
{

}

