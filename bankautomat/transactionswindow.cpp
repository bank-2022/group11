#include "transactionswindow.h"
#include "ui_transactionswindow.h"
#include "mainwindow.h"

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);

    transactionsWindowTimer = new QTimer();
    transactionsWindowTimer->setInterval(10000);  // timer for 10 seconds
    transactionsWindowTimer->setSingleShot(false); // timer works more than once

    // if the timer has ran out, this window will be closed
    connect(transactionsWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
    ui = nullptr;

    delete transactionsWindowTimer;
    transactionsWindowTimer = nullptr;
}

void TransactionsWindow::startTransactionsWindowTimer()
{
    transactionsWindowTimer->start();
}

void TransactionsWindow::reStartTransactionsWindowTimer()
{
    transactionsWindowTimer->stop();
    transactionsWindowTimer->start();
}

void TransactionsWindow::on_nextButton_clicked()
{
    transactionsWindowTimer->stop();
    transactionsWindowTimer->start();
}


void TransactionsWindow::on_previousButton_clicked()
{
    transactionsWindowTimer->stop();
    transactionsWindowTimer->start();
}


void TransactionsWindow::on_exitButton_clicked()
{
    this-> close();
}

