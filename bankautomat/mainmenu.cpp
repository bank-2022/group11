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

    pRestApiInterfaceClass = api;
    pDonationWindow = new DonationWindow(parent, this, pRestApiInterfaceClass);
    pTransactionsWindow = new TransactionsWindow(parent, this, pRestApiInterfaceClass);
    pWithdrawWindow = new WithdrawWindow(parent, this, pRestApiInterfaceClass);

    mainMenuTimer = new QTimer();
    mainMenuTimer->setInterval(30000);  // 30 s timer
    mainMenuTimer->setSingleShot(true);

    qRegisterMetaType<QVector<QString>>("QVector<QString");
    qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");

    // if the 30 s timer has ran out, this window will be closed
    connect(mainMenuTimer, SIGNAL(timeout()),
            this, SLOT(on_logOutButton_clicked()));

    // rest api functions
    connect(pRestApiInterfaceClass, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass,
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
    ui->nameLabel->setText("Hello "+ name);
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


void MainMenu::print5Transactions()
{
    on_refreshButton_clicked();
}


void MainMenu::update5List(QVector<QVector<QString>> list)
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));

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


void MainMenu::on_refreshButton_clicked()
{
    // This function updates the balance and transactions
    // on the main menu window when the
    // refresh button is clicked.

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    reStartMainMenuTimer();
    pRestApiInterfaceClass->getBalance(accountNumber);
    pRestApiInterfaceClass->get5Transactions(accountNumber);
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


void MainMenu::on_logOutButton_clicked()
{
    mainMenuTimer->stop();
    this->close(); // Logs out of the system and closes the main menu window.
}
