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

}

Pincode::~Pincode()
{
    delete ui;
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

void Pincode::loginSuccessful(bool locked)
{
    if (locked == true){
        ui->label_2->setText("Card locked");
    }
    else {
        ui->label_2->setText("Login successful");
        emit getType();
    }
}

void Pincode::loginFailed(QString message)
{
    ui->lineEdit->clear();
    if (message != "Error connecting to server" ||
        message != "Database error"){
        loginAttempts++;
    }
    ui->label_2->setText(message);

    if (loginAttempts >= 3){
        ui->label_2->setText("Card locked");
        emit putLocked("yes");
    }
}

void Pincode::on_B1_clicked()
{
    pinNumber("1");
    pinFlag = true;
}


void Pincode::on_B2_clicked()
{
    pinNumber("2");
    pinFlag = true;
}


void Pincode::on_B3_clicked()
{
    pinNumber("3");
    pinFlag = true;
}


void Pincode::on_B4_clicked()
{
    pinNumber("4");
    pinFlag = true;
}


void Pincode::on_B5_clicked()
{
    pinNumber("5");
    pinFlag = true;
}


void Pincode::on_B6_clicked()
{
    pinNumber("6");
    pinFlag = true;
}


void Pincode::on_B7_clicked()
{
    pinNumber("7");
    pinFlag = true;
}


void Pincode::on_B8_clicked()
{
    pinNumber("8");
    pinFlag = true;
}


void Pincode::on_B9_clicked()
{
    pinNumber("9");
    pinFlag = true;
}


void Pincode::on_BBack_clicked()
{
    ui->lineEdit->clear();
    pinFlag = false;
}


void Pincode::on_B0_clicked()
{
    pinNumber("0");
    pinFlag = true;
}


void Pincode::on_BEnter_clicked()
{
    QString pin = ui->lineEdit->text();
    emit sendPincode(pin);
}

