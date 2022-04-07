#include "mainwindow.h"
#include "ui_mainwindow.h"

/* This is the first window that opens when the program starts.
   The window asks the user to insert the card to the RFID reader
   and then the pin ui opens. */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainMenu = new MainMenu;
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;

    delete pMainMenu;
    pMainMenu = nullptr;
}


void MainWindow::on_mainMenuButton_clicked()
{
    pMainMenu->show();
    pMainMenu->startMainMenuTimer();
}

