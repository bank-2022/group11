#include "mainwindow.h"
#include "ui_mainwindow.h"

/* This is the first window that opens when the program starts.
   The window asks the user to insert the card to the RFID reader
   and then the pin ui opens. */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul");

    pRestApiInterfaceClass = new DLLRestApi;
    pRestApiInterfaceClass->setBaseURL("http://localhost:3000");

    pMainMenu = new MainMenu(parent, this, pRestApiInterfaceClass);

    qRegisterMetaType<QVector<QString>>("QVector<QString");

    // rest api functions
    connect(pRestApiInterfaceClass, SIGNAL(loginSuccessful()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(loginFailed(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(forbiddenAccess()),
            this, SLOT(forbiddenAccessDetected()), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass,SIGNAL(customerInfo(QVector<QString>)),
            this, SLOT(updateCustomerInfo(QVector<QString>)),Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(type(QString)),
            this, SLOT(updateType(QString)), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;

    delete pMainMenu;
    pMainMenu = nullptr;

    delete pRestApiInterfaceClass;
    pRestApiInterfaceClass = nullptr;
}


/* Login functions */
void MainWindow::loginSuccessfulSlot()
{
    ui->warningLabel->setText("Login Successful!");
    pMainMenu->show();
    pMainMenu->startMainMenuTimer();

    getCustomerInfo();
    getCustomerType();
    get5Transactions();
    pMainMenu->print5Transactions();
}


void MainWindow::loginFailedSlot(QString message)
{
    ui->warningLabel->setText(message + "!");
}


void MainWindow::forbiddenAccessDetected()
{
    ui->warningLabel->setText("FORBIDDEN");
}


void MainWindow::on_ruusuButton_clicked()
{
    accountNumber = "FI4278907654123400";
    cardNumber = "66778899";
    cardPin = "5566";
    pRestApiInterfaceClass->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
    pMainMenu->getAccountNumber(accountNumber);
}


void MainWindow::on_olaviButton_clicked()
{
    accountNumber = "FI5566778899";
    cardNumber = "0987666";
    cardPin = "1234";
    pRestApiInterfaceClass->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
    pMainMenu->getAccountNumber(accountNumber);
}


void MainWindow::on_failLoginButton_clicked()
{
    accountNumber = "FI5566778899";
    cardNumber = "0987666";
    cardPin = "666";
    pRestApiInterfaceClass->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
    pMainMenu->getAccountNumber(accountNumber);
}


/* Customer info functions */
void MainWindow::getCustomerInfo()
{
    pRestApiInterfaceClass->getCustomerInfo(cardNumber);
}


void MainWindow::updateCustomerInfo(QVector<QString> info)
{
    name = info[0];
    accountNumber = info[1];

    pMainMenu->printName(name);
    pMainMenu->printAccountNumber(accountNumber);
}


void MainWindow::getCustomerType()
{
    pRestApiInterfaceClass->getType(cardNumber);
}


void MainWindow::updateType(QString type)
{
    pMainMenu->printType(type);

}


void MainWindow::updateBalance(long long balance)
{
    QString stringBalance = convertToEuros(balance);
    pMainMenu->printBalance(stringBalance);
}


void MainWindow::get5Transactions()
{
    pRestApiInterfaceClass->get5Transactions(cardNumber);
}


QString MainWindow::convertToEuros(long long sum)
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

