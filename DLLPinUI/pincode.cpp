#include "pincode.h"
#include "ui_pincode.h"

Pincode::Pincode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pincode)
{
    ui->setupUi(this);
    napit.append(ui->B1);
    napit.append(ui->B2);
    napit.append(ui->B3);
    napit.append(ui->B4);
    napit.append(ui->B5);
    napit.append(ui->B6);
    napit.append(ui->B7);
    napit.append(ui->B8);
    napit.append(ui->B9);

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
    if (pinFlag == true){
        pin.append(x);
        ui->lineEdit->setText(pin);
  }
    else if (pinFlag == false){
        pin = x;
        ui->lineEdit->clear();
        ui->lineEdit->setText(pin);
        pinFlag = true;
    }
}

void Pincode::loginSuccessful()
{
    if (locked == false){
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
        message != "Database error"){
        loginAttempts++;
    }
    ui->label_2->setText(message);

    if (loginAttempts >= 3){
        locked = true;
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
    pinNumber("1");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B2_clicked()
{
    pinNumber("2");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B3_clicked()
{
    pinNumber("3");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B4_clicked()
{
    pinNumber("4");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B5_clicked()
{
    pinNumber("5");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B6_clicked()
{
    pinNumber("6");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B7_clicked()
{
    pinNumber("7");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B8_clicked()
{
    pinNumber("8");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_B9_clicked()
{
    pinNumber("9");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_BBack_clicked()
{
    ui->lineEdit->clear();
    pinFlag = false;
    restartPincodeTimer();
}


void Pincode::on_B0_clicked()
{
    pinNumber("0");
    pinFlag = true;
    restartPincodeTimer();
}


void Pincode::on_BEnter_clicked()
{
    QString pin = ui->lineEdit->text();
    emit sendPincode(pin);
    pincodeTimer->stop();
}

