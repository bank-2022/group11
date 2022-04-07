#include "mainmenu.h"
#include "ui_mainmenu.h"

/* In this window the user will be able to view their account information
   (name, balance, accountnumber) and their five last transactions. The
   user can also choose to withdraw money, donate money, view transactions
   in more depth or log out of the system. */

MainMenu::MainMenu(QWidget *parent, MainWindow *ptr) :
    QDialog(parent), ui(new Ui::MainMenu), pMainWindow(ptr)
{
    ui->setupUi(this);
    pDonationWindow = new DonationWindow;
    pTransactionsWindow = new TransactionsWindow;
    pWithdrawWindow = new WithdrawWindow;

    mainMenuTimer = new QTimer();
    mainMenuTimer->setInterval(30000);  // timer for 30 seconds
    mainMenuTimer->setSingleShot(true); // timer is set to time out only once
    mainMenuTimer->start();

    // if the timer has ran out, this window and the connection to the database will be closed
    connect(mainMenuTimer, SIGNAL(timeout()),
            this, SLOT(on_logOutButton_clicked()));
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
}


void MainMenu::startTimer()
{
    mainMenuTimer->start();
}


void MainMenu::reStartTimer()
{
    mainMenuTimer->stop();
    mainMenuTimer->start();
}


void MainMenu::on_withdrawButton_clicked()
{
    mainMenuTimer->stop(); // if a button is clicked, the timer will stop
    pWithdrawWindow->show(); // Opens a window where the user can withdraw money.
}


void MainMenu::on_transactionsButton_clicked()
{
    mainMenuTimer->stop();
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
}


void MainMenu::on_donateButton_clicked()
{
    mainMenuTimer->stop();
    pDonationWindow->show(); // Opens a window where the user can donate money.
}


void MainMenu::on_logOutButton_clicked()
{
    mainMenuTimer->stop();
    this->close(); // Logs out of the system and closes the mainWindow.
}


void MainMenu::on_refreshButton_clicked()
{
    mainMenuTimer->stop();
    // Updates the balance.
    mainMenuTimer->start();
}
