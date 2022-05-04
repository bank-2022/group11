#include "pincode.h"
#include "ui_pincode.h"

Pincode::Pincode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pincode)
{
    ui->setupUi(this);
    this->setWindowTitle("Turtle Software Banksimul - Login");

    loginAttempts = 0;
    locked = false;

    pincodeTimer = new QTimer();
    pincodeTimer->setInterval(10000);
    pincodeTimer->setSingleShot(false);

    connect(pincodeTimer, SIGNAL(timeout()),
            this, SLOT(close()),
            Qt::QueuedConnection);

}

Pincode::~Pincode()
{
    delete ui;
    ui = nullptr;
    delete pincodeTimer;
    pincodeTimer = nullptr;
}

void Pincode::pinNumber(QString x)
{
    if (pinFlag == true) {
        pin.append(x);
        ui->lineEdit->setText(pin);
  }
    else if (pinFlag == false) {
        pin = x;
        ui->lineEdit->clear();
        ui->lineEdit->setText(pin);
        pinFlag = true;
    }
}

void Pincode::loginSuccessful()
{
    if (locked == false) {
        emit getType();
    }
    else {
        ui->label_2->setText("Card locked");
    }
}

void Pincode::loginFailed(QString message)
{
    ui->lineEdit->clear();
    pinFlag = false;
    if (message != "Error connecting to server" ||
        message != "Database error") {
        loginAttempts++;
    }
    ui->label_2->setText(message);

    if (loginAttempts >= 3) {
        locked = true;
        restartPincodeTimer();
        ui->label_2->setText("Card locked");
    }
}

void Pincode::startPincodeTimer()
{
    pincodeTimer->start();
}

void Pincode::restartPincodeTimer()
{
    pincodeTimer->stop();
    pincodeTimer->start();
}

void Pincode::on_B1_clicked()
{
    if (locked == false) {
        pinNumber("1");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B2_clicked()
{
    if (locked == false) {
        pinNumber("2");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B3_clicked()
{
    if (locked == false) {
        pinNumber("3");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B4_clicked()
{
    if (locked == false) {
        pinNumber("4");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B5_clicked()
{
    if (locked == false) {
        pinNumber("5");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B6_clicked()
{
    if (locked == false) {
        pinNumber("6");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B7_clicked()
{
    if (locked == false) {
        pinNumber("7");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B8_clicked()
{
    if (locked == false) {
        pinNumber("8");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_B9_clicked()
{
    if (locked == false) {
        pinNumber("9");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_BBack_clicked()
{
    if (locked == false) {
        ui->lineEdit->clear();
        pinFlag = false;
        restartPincodeTimer();
    }
}


void Pincode::on_B0_clicked()
{
    if (locked == false) {
        pinNumber("0");
        pinFlag = true;
        restartPincodeTimer();
    }
}


void Pincode::on_BEnter_clicked()
{
    if (locked == false) {
        QString pin = ui->lineEdit->text();
        emit sendPincode(pin);
        pincodeTimer->stop();
    }
}

void Pincode::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    ui->lineEdit->clear();
    pinFlag = false;
}

