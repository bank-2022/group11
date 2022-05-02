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

    pRestApi = new DLLRestApi;
    pRestApi->setBaseURL("http://localhost:3000");

    pMainMenu = new MainMenu(parent, this, pRestApi);

    qRegisterMetaType<QVector<QString>>("QVector<QString");

    // rest api functions
    connect(pRestApi, SIGNAL(loginSuccessful()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(loginFailed(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(forbiddenAccess()),
            this, SLOT(forbiddenAccessDetected()), Qt::QueuedConnection);

    connect(pRestApi,SIGNAL(customerInfo(QVector<QString>)),
            this, SLOT(updateCustomerInfo(QVector<QString>)),Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(type(QString)),
            this, SLOT(updateType(QString)), Qt::QueuedConnection);

    connect(pRestApi, SIGNAL(balance(long long)),
            this, SLOT(updateBalance(long long)), Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;

    delete pMainMenu;
    pMainMenu = nullptr;

    delete pRestApi;
    pRestApi = nullptr;
}


/* Login functions */
void MainWindow::loginSuccessfulSlot()
{
    ui->warningLabel->setText("Login Successful!");

    getCustomerInfo();
    getCustomerType();
    get5Transactions();

    pMainMenu->show();
    pMainMenu->startMainMenuTimer();


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
    cardNumber = "66778899";
    cardPin = "5566";
    pRestApi->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
}


void MainWindow::on_olaviButton_clicked()
{
    cardNumber = "0987666";
    cardPin = "1234";
    pRestApi->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
}


void MainWindow::on_failLoginButton_clicked()
{
    cardNumber = "0987666";
    cardPin = "666";
    pRestApi->login(cardNumber, cardPin);
    pMainMenu->getCardNumber(cardNumber);
}


/* Customer info functions */
void MainWindow::getCustomerInfo()
{
    pRestApi->getCustomerInfo(cardNumber);
}


void MainWindow::updateCustomerInfo(QVector<QString> info)
{
    name = info[0];
    accountNumber = info[1];

    pMainMenu->printName(name);
    pMainMenu->printAccountNumber(accountNumber);
    pMainMenu->getAccountNumber(accountNumber);
    pMainMenu->print5Transactions(accountNumber);
}


void MainWindow::getCustomerType()
{
    pRestApi->getType(cardNumber);
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
    pRestApi->get5Transactions(cardNumber);
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

