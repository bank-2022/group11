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
}


MainWindow::~MainWindow()
{
    delete ui;
    delete pMainMenu;
    delete pRestApiInterfaceClass;
}


void MainWindow::loginSuccessfulSlot()
{
    ui->warningLabel->setText("Login Successful!");
    pMainMenu->show();
    getCustomerInfo();
    getCustomerType();
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
