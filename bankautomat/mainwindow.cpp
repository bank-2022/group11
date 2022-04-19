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

    pRestApiInterfaceClass = new RestApi;
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

    connect(pRestApiInterfaceClass,
            SIGNAL(transactions5(QVector<QVector<QString> >)),
            this, SLOT(updateList(QVector<QVector<QString> >)),
            Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete pMainMenu;
    delete pRestApiInterfaceClass;
}

/* Login functions */
void MainWindow::loginSuccessfulSlot()
{
    ui->warningLabel->setText("Login Successful!");
    pMainMenu->show();

    getBalance();
    getCustomerInfo();
    getCustomerType();
    get5Transactions();
}


void MainWindow::loginFailedSlot(QString message)
{
    ui->warningLabel->setText(message + "!");
}


void MainWindow::forbiddenAccessDetected()
{
    ui->warningLabel->setText("FORBIDDEN");
}


void MainWindow::on_mainMenuButton_clicked()
{
    cardNumber = "0987666";
    cardPin = "1234";
    pRestApiInterfaceClass->login(cardNumber, cardPin);
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

    qDebug() << info;
}


void MainWindow::getCustomerType()
{
    pRestApiInterfaceClass->getType(cardNumber);
}


void MainWindow::updateType(QString type)
{
    pMainMenu->printType(type);
}


void MainWindow::getBalance()
{
    pRestApiInterfaceClass->getBalance(cardNumber);
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

void MainWindow::updateList(QVector<QVector<QString>> list)
{
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

    pMainMenu->print5Transactions(table_model);
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
