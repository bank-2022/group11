#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
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

MainWindow::~MainWindow()
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


void MainWindow::startTimer()
{
    mainWindowTimer->start();
}


void MainWindow::reStartTimer()
{
    mainWindowTimer->stop();
    mainWindowTimer->start();
}


void MainWindow::on_withdrawButton_clicked()
{
    mainWindowTimer->stop();
    pWithdrawWindow->show(); // Opens a window where the user can withdraw money.
}


void MainWindow::on_viewTransactionsButton_clicked()
{
    mainWindowTimer->stop();
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
}


void MainWindow::on_donateButton_clicked()
{
    mainWindowTimer->stop();
    pDonationWindow->show(); // Opens a window where the user can donate money.
}


void MainWindow::on_logOutButton_clicked()
{
    mainWindowTimer->stop();
    this->close(); // Logs out of the system and closes the mainWindow.
}


void MainWindow::on_refreshButton_clicked()
{
    mainWindowTimer->stop();
    // Updates the balance.
    mainWindowTimer->start();
}

