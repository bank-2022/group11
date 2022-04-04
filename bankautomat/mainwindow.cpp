#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pDonationWindow = new DonationWindow;
    pTransactionsWindow = new TransactionsWindow;
    pWithdrawWindow = new WithdrawWindow;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pDonationWindow;
    delete pTransactionsWindow;
    delete pWithdrawWindow;
}


void MainWindow::on_withdrawButton_clicked()
{
    pWithdrawWindow->show(); // Opens a window where the user can withdraw money.
}


void MainWindow::on_viewTransactionsButton_clicked()
{
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
}


void MainWindow::on_donateButton_clicked()
{
    pDonationWindow->show(); // Opens a window where the user can donate money.
}


void MainWindow::on_logOutButton_clicked()
{
    this->close(); // Logs out of the system and closes the mainWindow.
}


void MainWindow::on_refreshButton_clicked()
{
    // Updates the balance.
}

