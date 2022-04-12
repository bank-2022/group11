#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"

/* In this window the user will be able to view their account information
   (name, balance, accountnumber) and their five last transactions. The
   user can also choose to withdraw money, donate money, view transactions
   in more depth or log out of the system. */

MainMenu::MainMenu(QWidget *parent, MainWindow *ptr, RestApi *api) :
    QDialog(parent), ui(new Ui::MainMenu), pMainWindow(ptr)
{
    ui->setupUi(this);

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
    connect(pRestApiInterfaceClass,SIGNAL(customerInfo(QVector<QString>)),
            this, SLOT(updateCustomerInfo(QVector<QString>)),Qt::QueuedConnection);


}


MainMenu::~MainMenu()
{
    delete ui;
    ui = nullptr;

    delete pDonationWindow;
    pDonationWindow = nullptr;

    delete pTransactionsWindow;
    pTransactionsWindow = nullptr;

    delete pWithdrawWindow;
    pWithdrawWindow = nullptr;

    delete mainMenuTimer;
    mainMenuTimer = nullptr;
}


void MainMenu::updateCustomerInfo(QVector<QString> info)
{
    ui->nameLabel->setText(info[0]);
    ui->accountNumberLabel->setText(info[1]);
    qDebug() << info;
}


void MainMenu::on_refreshButton_clicked()
{
    // This function updates the balance and customer info
    // on the main menu window when the
    // refresh button is clicked.

    mainMenuTimer->stop();
    pRestApiInterfaceClass->getCustomerInfo("0987666");
    mainMenuTimer->start();
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
