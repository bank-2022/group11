#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, MainWindow *ptr) :
    QDialog(parent), ui(new Ui::MainMenu), pMainWindow(ptr)
{
    ui->setupUi(this);
    pDonationWindow = new DonationWindow;
    pTransactionsWindow = new TransactionsWindow;
    pWithdrawWindow = new WithdrawWindow;

    mainWindowTimer = new QTimer();
    mainWindowTimer->setInterval(30000);
    mainWindowTimer->setSingleShot(true); // timer is set to time out only once
    mainWindowTimer->start();

    connect(mainWindowTimer, SIGNAL(timeout()),
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
    mainWindowTimer->start();
}


void MainMenu::reStartTimer()
{
    mainWindowTimer->stop();
    mainWindowTimer->start();
}


void MainMenu::on_withdrawButton_clicked()
{
    mainWindowTimer->stop();
    pWithdrawWindow->show(); // Opens a window where the user can withdraw money.
}


void MainMenu::on_transactionsButton_clicked()
{
    mainWindowTimer->stop();
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
}


void MainMenu::on_donateButton_clicked()
{
    mainWindowTimer->stop();
    pDonationWindow->show(); // Opens a window where the user can donate money.
}


void MainMenu::on_logOutButton_clicked()
{
    mainWindowTimer->stop();
    this->close(); // Logs out of the system and closes the mainWindow.
}


void MainMenu::on_refreshButton_clicked()
{
    mainWindowTimer->stop();
    // Updates the balance.
    mainWindowTimer->start();
}
