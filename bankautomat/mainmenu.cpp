#include "mainmenu.h"
#include "ui_mainmenu.h"


/* In this window the user will be able to view their account information
 * (name, balance and accountnumber) and their five last transactions. The
 * user can also choose to withdraw money, donate money, view all transactions
 * or log out of the system. */


MainMenu::MainMenu(QWidget *parent, MainWindow *ptr, DLLRestApi *api) :
    QDialog(parent),
    ui(new Ui::MainMenu),
    pMainWindow(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Main Menu");

    pRestApi = api;
    pDonationWindow = new DonationWindow(parent, this, pRestApi);
    pTransactionsWindow = new TransactionsWindow(parent, this, pRestApi);
    pWithdrawWindow = new WithdrawWindow(parent, this, pRestApi);

    mainMenuTimer = new QTimer();
    mainMenuTimer->setInterval(30000);  // 30 s timer
    mainMenuTimer->setSingleShot(true);

    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");

    // if the 30 s timer has ran out, this window will be closed
    connect(mainMenuTimer, SIGNAL(timeout()),
            this, SLOT(on_logOutButton_clicked()));

    // rest api functions
    connect(pRestApi, SIGNAL(transactionComplete()),
            this, SLOT(updateTransactions()), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);

    connect(pRestApi,
            SIGNAL(transactions5(QVector<QVector<QString> >)),
            this, SLOT(update5List(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}


MainMenu::~MainMenu()
{
    delete ui;
    ui = nullptr;

    delete mainMenuTimer;
    mainMenuTimer = nullptr;

    delete pDonationWindow;
    pDonationWindow = nullptr;

    delete pTransactionsWindow;
    pTransactionsWindow = nullptr;

    delete pWithdrawWindow;
    pWithdrawWindow = nullptr;
}


/* customer info functions */
void MainMenu::printName(QString name)
{
    /* prints the name on main menu and sends
     * the name to be printed in other windows too */

    ui->nameLabel->setText("Hello, "+ name);

    pWithdrawWindow->printName(name);
    pDonationWindow->printName(name);
    pTransactionsWindow->printName(name);
}


void MainMenu::printAccountNumber(QString accountNum)
{
    /* prints the account number on main menu and sends
     * the account number to be printed in other windows too */

    accountNumber = accountNum;
    ui->accountNumberLabel->setText("Account: "+accountNumber);

    pWithdrawWindow->printAccountNumber(accountNumber);
    pDonationWindow->printAccountNumber(accountNumber);
    pTransactionsWindow->printAccountNumber(accountNumber);

    getAccountNumber(accountNumber); // !!
}


void MainMenu::printType(QString type)
{
    /* prints the card type (credit / debit)
     * to main menu and sends the type to be printed
     * in other windows too */

    ui->typeLabel->setText(type);

    pWithdrawWindow->printType(type);
    pDonationWindow->printType(type);
    pTransactionsWindow->printType(type);
}


void MainMenu::printBalance(QString balance)
{
    /* prints the balance to main menu and sends
     * the type to be printed in other windows too */

    ui->balanceLabel->setText("Balance: "+balance+" €");

    pWithdrawWindow->printBalance(balance);
    pDonationWindow->printBalance(balance);
    pTransactionsWindow->printBalance(balance);
}


void MainMenu::print5Transactions(QString accountNum)
{
    /* prints the balance and transactions on main
     * menu as it opens*/

    accountNumber = accountNum;
    pRestApi->getBalance(accountNumber);
    pRestApi->get5Transactions(accountNumber);
}


void MainMenu::updateTransactions()
{
    /* updates the balance and transactions on main menu after
     * a transaction (withdrawal / donation) is done */

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    pRestApi->getBalance(accountNumber);
    pRestApi->get5Transactions(accountNumber);
}


void MainMenu::update5List(QVector<QVector<QString>> list)
{
    /* creates the list (table widget) for transactions that are
     * visible on the main menu */

    QApplication::setStyle(QStyleFactory::create("Fusion"));
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


void MainMenu::getCardNumber(QString cardnumber)
{
    /* shares the card number to other windows in need */

    cardNumber = cardnumber;
    pDonationWindow->getCardNumber(cardNumber);
    pWithdrawWindow->getCardNumber(cardNumber);
}

void MainMenu::getAccountNumber(QString accountNum)
{
    /* saves the accountnumber to variable */
    accountNumber = accountNum;
}


void MainMenu::updateBalance(long long balance)
{
    /* updates the balance */
    QString stringBalance = convertToEuros(balance);
    ui->balanceLabel->setText(stringBalance);
}


QString MainMenu::convertToEuros(long long sum)
{
    /* converts a long long of cents to a string of euros */

    int cents = abs(sum % 100);
    QString centString;
    if (cents < 10)
    {
        centString = "0" + QString::number(cents);
    }
    else
    {
        centString = QString::number(cents);
    }
    return QString::number(sum / 100) + "." + centString;
}


/* timer functions */
void MainMenu::startMainMenuTimer()
{
    mainMenuTimer->start();
}


void MainMenu::reStartMainMenuTimer()
{
    mainMenuTimer->stop();
    mainMenuTimer->start();
}


/* button functions */
void MainMenu::on_withdrawButton_clicked()
{
    /* stops the main menu timer,
     * opens a window where the user can withdraw money
     * and starts the withdraw window timer*/

    mainMenuTimer->stop();
    pWithdrawWindow->show();
    pWithdrawWindow->startWithdrawWindowTimer();
}


void MainMenu::on_transactionsButton_clicked()
{
    /* stops the main menu timer,
     * opens a window where the user can view their transactions
     * and starts the transactions window timer*/

    mainMenuTimer->stop();
    pTransactionsWindow->showTransactions(accountNumber);
    pTransactionsWindow->show();
    pTransactionsWindow->startTransactionsWindowTimer();
}


void MainMenu::on_donateButton_clicked()
{
    /* stops the main menu timer,
     * opens a window where the user can donate money
     * and starts the donation window timer*/

    mainMenuTimer->stop();
    pDonationWindow->show();
    pDonationWindow->startDonationWindowTimer();
}


void MainMenu::on_logOutButton_clicked()
{
    /* stops the main menu timer,
     * clears all windows
     * and closes main menu window */

    mainMenuTimer->stop();
    pWithdrawWindow->clearWithdrawWindow();
    pDonationWindow->clearDonationWindow();
    pTransactionsWindow->clearTransactionsWindow();
    clearMainMenuWindow();

    this->close();
}


void MainMenu::clearMainMenuWindow()
{
    ui->accountNumberLabel->clear();
    ui->balanceLabel->clear();
    ui->nameLabel->clear();
    ui->typeLabel->clear();
}
