#include "mainmenu.h"
#include "ui_mainmenu.h"


/* In this window the user will be able to view their account information
   (name, balance, accountnumber) and their five last transactions. The
   user can also choose to withdraw money, donate money, view transactions
   in more depth or log out of the system. */


MainMenu::MainMenu(QWidget *parent, MainWindow *ptr, DLLRestApi *api) :
    QDialog(parent),
    ui(new Ui::MainMenu),
    pMainWindow(ptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul");

    pRestApi = api;
    pDonationWindow = new DonationWindow(parent, this, pRestApi);
    pTransactionsWindow = new TransactionsWindow(parent, this, pRestApi);
    pWithdrawWindow = new WithdrawWindow(parent, this, pRestApi);

    mainMenuTimer = new QTimer();
    mainMenuTimer->setInterval(30000);  // 30 s timer
    mainMenuTimer->setSingleShot(true);

    qRegisterMetaType<QVector<QString>>("QVector<QString");
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


void MainMenu::printName(QString name)
{
    ui->nameLabel->setText("Hello, "+ name);
    pWithdrawWindow->printName(name);
    pDonationWindow->printName(name);
    pTransactionsWindow->printName(name);
}


/* customer info functions */
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


void MainMenu::updateTransactions()
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    reStartMainMenuTimer();
    pRestApi->getBalance(accountNumber);
    pRestApi->get5Transactions(accountNumber);
}


void MainMenu::print5Transactions()
{
    // This function updates the balance and transactions
    // on the main menu window as it opens

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    reStartMainMenuTimer();
    pRestApi->getBalance(accountNumber);
    pRestApi->get5Transactions(accountNumber);
}


void MainMenu::update5List(QVector<QVector<QString>> list)
{
    //QApplication::setStyle(QStyleFactory::create("Fusion"));

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
    pDonationWindow->getCardNumber(cardnumber);
    pWithdrawWindow->getCardNumber(cardnumber);
}

void MainMenu::getAccountNumber(QString accountnum)
{
    accountNumber = accountnum;
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
    {
        centString = "0" + QString::number(cents);
    }
    else
    {
        centString = QString::number(cents);
    }
    return QString::number(sum / 100) + "." + centString;
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
    pTransactionsWindow->showTransactions(accountNumber);
    pTransactionsWindow->show(); // Opens a window where the user can view transactions.
    pTransactionsWindow->startTransactionsWindowTimer();
}


void MainMenu::on_donateButton_clicked()
{
    mainMenuTimer->stop();
    pDonationWindow->show(); // Opens a window where the user can donate money.
    pDonationWindow->startDonationWindowTimer();
}


void MainMenu::clearMainMenuWindow()
{
    ui->accountNumberLabel->clear();
    ui->balanceLabel->clear();
    ui->nameLabel->clear();
    ui->typeLabel->clear();


}


void MainMenu::on_logOutButton_clicked()
{
    mainMenuTimer->stop();
    pWithdrawWindow->clearWithdrawWindow();
    pDonationWindow->clearDonationWindow();
    pTransactionsWindow->clearTransactionsWindow();
    clearMainMenuWindow();


    this->close();
}
