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
    pRestApiInterfaceClass = new RestApi;
    pRestApiInterfaceClass->setBaseURL("http://localhost:3000");

    pMainMenu = new MainMenu;

    connect(pRestApiInterfaceClass, SIGNAL(loginSuccessful()),
            this, SLOT(loginSuccessfulSlot()), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(loginFailed(QString)),
            this, SLOT(loginFailedSlot(QString)), Qt::QueuedConnection);

    connect(pRestApiInterfaceClass, SIGNAL(forbiddenAccess()),
            this, SLOT(forbiddenAccessDetected()), Qt::QueuedConnection);
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


void MainWindow::loginSuccessfulSlot()
{
    ui->warningLabel->setText("Login Successful!");
    pMainMenu->show();
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
