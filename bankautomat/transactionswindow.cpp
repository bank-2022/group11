#include "transactionswindow.h"
#include "ui_transactionswindow.h"
#include "mainwindow.h"

TransactionsWindow::TransactionsWindow(QWidget *parent, MainWindow *ptr,RestApi *api) :
    QDialog(parent), ui(new Ui::TransactionsWindow), pMainWindow(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Transactions");

    pRestApiInterfaceClass = api;

    transactionsWindowTimer = new QTimer();
    transactionsWindowTimer->setInterval(10000);  // timer for 10 seconds
    transactionsWindowTimer->setSingleShot(false); // timer works more than once

    // if the timer has ran out, this window will be closed
    connect(transactionsWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));

    //connect(pRestApiInterfaceClass,
            //SIGNAL(transactions10(QVector<QVector<QString> >)),
            //this, SLOT(updateList(QVector<QVector<QString> >)),
           // Qt::QueuedConnection);

   // pRestApiInterfaceClass->get10Transactions("FI5566778899", 0);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
    delete transactionsWindowTimer;
}


void TransactionsWindow::printName(QString name)
{
    ui->nameLabel->setText(name);
}


void TransactionsWindow::printAccountNumber(QString accountNumber)
{
    ui->accountNumberLabel->setText(accountNumber);
}


void TransactionsWindow::printType(QString type)
{
    ui->typeLabel->setText(type);
}

void TransactionsWindow::printBalance(QString balance)
{
    ui->balanceLabel->setText(balance);
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


/*void TransactionsWindow::updateList(QVector<QVector<QString>> list)
{
    QStandardItemModel *table_model =
            new QStandardItemModel(list.size(), 3);

    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Time"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Transaction"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Amount"));

    for (short i = 0; i < list.size(); i++) {
        QStandardItem *time = new QStandardItem(list[i][0]);
        table_model->setItem(i, 0, time);
        QStandardItem *transaction = new QStandardItem(list[i][1]);
        table_model->setItem(i, 1, transaction);
        QStandardItem *amount = new QStandardItem(list[i][2]);
        table_model->setItem(i, 2, amount);
    }
    ui->transactionsList->setModel(table_model);

}
*/

void TransactionsWindow::on_exitButton_clicked()
{
    this-> close();
}

