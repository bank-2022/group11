#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"

/* In this window the user will be able to view their account information
   (name, balance, accountnumber) and their five last transactions. The
   user can also choose to withdraw money, donate money, view transactions
   in more depth or log out of the system. */

MainMenu::MainMenu(QWidget *parent, MainWindow *ptr, RestApi *api) :
    QDialog(parent),
    ui(new Ui::MainMenu),
    pMainWindow(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul");

    pDonationWindow = new DonationWindow;
    pTransactionsWindow = new TransactionsWindow;
    pWithdrawWindow = new WithdrawWindow;
    pRestApiInterfaceClass = api;

    mainMenuTimer = new QTimer();
    mainMenuTimer->setInterval(30000);  // timer for 30 seconds
    mainMenuTimer->setSingleShot(true); // timer is set to time out only once

    qRegisterMetaType<QVector<QString>>("QVector<QString");
    qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");

    // if the timer has ran out, this window and the connection to the database will be closed
    connect(mainMenuTimer, SIGNAL(timeout()),
            this, SLOT(on_logOutButton_clicked()));

    // rest api functions
    connect(pRestApiInterfaceClass, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass,
            SIGNAL(transactions5(QVector<QVector<QString> >)),
            this, SLOT(updateList(QVector<QVector<QString> >)),
            Qt::QueuedConnection);

    connect(pRestApiInterfaceClass,
            SIGNAL(transactions10(QVector<QVector<QString> >)),
            this, SLOT(updateList(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}


MainMenu::~MainMenu()
{
    delete ui;
    delete pDonationWindow;
    delete pTransactionsWindow;
    delete pWithdrawWindow;
    delete mainMenuTimer;
}


void MainMenu::printName(QString name)
{
    ui->nameLabel->setText(name);
    pWithdrawWindow->printName(name);
    pDonationWindow->printName(name);
    pTransactionsWindow->printName(name);
}


void MainMenu::printAccountNumber(QString accountNumber)
{
    ui->accountNumberLabel->setText(accountNumber);
    pWithdrawWindow->printAccountNumber(accountNumber);
    pDonationWindow->printAccountNumber(accountNumber);
    pTransactionsWindow->printAccountNumber(accountNumber);
}


void MainMenu::printType(QString type)
{
    ui->typeLabel->setText(type);
    pWithdrawWindow->printType(type);
    pDonationWindow->printType(type);
    pTransactionsWindow->printType(type);
}

void MainMenu::printBalance(QString balance)
{
    ui->balanceLabel->setText(balance);
    pWithdrawWindow->printBalance(balance);
    pDonationWindow->printBalance(balance);
    pTransactionsWindow->printBalance(balance);
}

void MainMenu::print5Transactions(QAbstractItemModel * list)
{
    ui->fiveTransactionsTableView->setModel(list);
}


void MainMenu::updateBalance(long long balance)
{
    QString stringBalance = convertToEuros(balance);
    ui->balanceLabel->setText(stringBalance);
}


QString MainMenu::convertToEuros(long long sum)
{
    // This function converts a long long of cents
    // to a string of euros

    int cents = abs(sum % 100);
    QString centString;
    if (cents < 10)
        centString = "0" + QString::number(cents);
    else
        centString = QString::number(cents);

    return QString::number(sum / 100) + "." + centString;
}


void MainMenu::updateList(QVector<QVector<QString>> list)
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
    ui->fiveTransactionsTableView->setModel(table_model);

}


void MainMenu::on_refreshButton_clicked()
{
    // This function updates the balance and transactions
    // on the main menu window when the
    // refresh button is clicked.


    pRestApiInterfaceClass->getBalance("FI5566778899");
    pRestApiInterfaceClass->get5Transactions("FI5566778899");
    reStartMainMenuTimer();
}


void MainMenu::startMainMenuTimer()
{
    mainMenuTimer->start();
}


void MainMenu::reStartMainMenuTimer()
{
    mainMenuTimer->stop();
    mainMenuTimer->start();
}


void MainMenu::on_withdrawButton_clicked()
{
    mainMenuTimer->stop(); // If any button is clicked, the timer will stop.
    pWithdrawWindow->show(); // Opens a window where the user can withdraw money.
    pWithdrawWindow->startWithdrawWindowTimer(); // starts a timer of 10 s on the withdrawal window
}


void MainMenu::on_transactionsButton_clicked()
{
    mainMenuTimer->stop();
    //pTransactionsWindow->showTransactions("FI5566778899");
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
    pTransactionsWindow->startTransactionsWindowTimer();
}


void MainMenu::on_donateButton_clicked()
{
    mainMenuTimer->stop();
    pDonationWindow->show(); // Opens a window where the user can donate money.
    pDonationWindow->startDonationWindowTimer();
}


void MainMenu::on_logOutButton_clicked()
{
    mainMenuTimer->stop();
    this->close(); // Logs out of the system and closes the main menu window.
}
