#include "transactionswindow.h"
#include "ui_transactionswindow.h"

#include "mainwindow.h"

/* In this window the user will be able to view all transactions done on their account. The
 * user can also view their account information (name, balance and accountnumber).*/


TransactionsWindow::TransactionsWindow(QWidget *parent, MainMenu *ptr, DLLRestApi *api) :
    QDialog(parent),
    ui(new Ui::TransactionsWindow),
    pMainMenu(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Transactions");

    pRestApi = api;
    pMainMenu = ptr;

    transactionsWindowTimer = new QTimer();
    transactionsWindowTimer->setInterval(10000);  // 10 s timer
    transactionsWindowTimer->setSingleShot(false);

    // if the 10 s timer has ran out, this window will be closed
    connect(transactionsWindowTimer, SIGNAL(timeout()),
            this, SLOT(on_exitButton_clicked()));

    connect(pRestApi,
            SIGNAL(transactions10(QVector<QVector<QString> >)),
            this, SLOT(updateList(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}


TransactionsWindow::~TransactionsWindow()
{
    delete ui;
    ui = nullptr;

    delete transactionsWindowTimer;
    transactionsWindowTimer = nullptr;
}


/* customer info functions */
void TransactionsWindow::printName(QString name)
{
    ui->nameLabel->setText("Name: "+name);
}


void TransactionsWindow::printAccountNumber(QString accountNumber)
{
    ui->accountNumberLabel->setText("Account: "+accountNumber);
}


void TransactionsWindow::printType(QString type)
{
    ui->typeLabel->setText(type);
}


void TransactionsWindow::printBalance(QString balance)
{
    ui->balanceLabel->setText("Balance: "+balance+" €");
}


/* timer functions */
void TransactionsWindow::startTransactionsWindowTimer()
{
    transactionsWindowTimer->start();
}

void TransactionsWindow::reStartTransactionsWindowTimer()
{
    transactionsWindowTimer->stop();
    transactionsWindowTimer->start();
}

/* Functions for browsing transactions */
void TransactionsWindow::showTransactions(QString accountNumber)
{
    accountNum = accountNumber;
    index = 0;
    pRestApi->get10Transactions(accountNumber, index);
}


void TransactionsWindow::on_nextButton_clicked()
{
    reStartTransactionsWindowTimer();
    index += 10;
    pRestApi->get10Transactions(accountNum, index);
}


void TransactionsWindow::on_previousButton_clicked()
{
    reStartTransactionsWindowTimer();
    if (index != 0){
        index -= 10;
        pRestApi->get10Transactions(accountNum, index);
    }
    else {
        index = 0;
    }
}


void TransactionsWindow::updateList(QVector<QVector<QString>> list)
{
    ui->transactionsTableWidget->setRowCount(list.size());
    ui->transactionsTableWidget->setColumnCount(3);
    QStringList headers = {"Time", "Transaction", "Amount"};
    ui->transactionsTableWidget->setHorizontalHeaderLabels(headers);

    for (short i = 0; i < list.size(); i++) {
        QTableWidgetItem *time = new QTableWidgetItem(list[i][0]);
        ui->transactionsTableWidget->setItem(i, 0, time);
        QTableWidgetItem *transaction = new QTableWidgetItem(list[i][1]);
        ui->transactionsTableWidget->setItem(i, 1, transaction);
        QTableWidgetItem *amount = new QTableWidgetItem(list[i][2]);
        ui->transactionsTableWidget->setItem(i, 2, amount);
    }
}


void TransactionsWindow::clearTransactionsWindow()
{
    ui->accountNumberLabel->clear();
    ui->balanceLabel->clear();
    ui->nameLabel->clear();
    ui->typeLabel->clear();
    ui->transactionsTableWidget->clearSpans();
    this->close();
}


void TransactionsWindow::on_exitButton_clicked()
{
    /* stops the transactions window timer,
     * starts the main menu timer
     * and closes the transactions window */

    transactionsWindowTimer->stop();
    pMainMenu->startMainMenuTimer();
    this-> close();
}

