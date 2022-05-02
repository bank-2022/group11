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

}

Pincode::~Pincode()
{
    delete ui;
}

void Pincode::handleClick()
{
    QObject * sender = QObject::sender();
    qDebug() << sender->objectName();
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
    ui->label_2->setText("Login successful");
}

void Pincode::loginFailed(QString message)
{
    ui->label_2->setText(message);
}

void Pincode::on_B1_clicked()
{
    handleClick();
    pinNumber("1");
    pinFlag = true;
}


void Pincode::on_B2_clicked()
{
    handleClick();
    pinNumber("2");
    pinFlag = true;
}


void Pincode::on_B3_clicked()
{
    handleClick();
    pinNumber("3");
    pinFlag = true;
}


void Pincode::on_B4_clicked()
{
    handleClick();
    pinNumber("4");
    pinFlag = true;
}


void Pincode::on_B5_clicked()
{
    handleClick();
    pinNumber("5");
    pinFlag = true;
}


void Pincode::on_B6_clicked()
{
    handleClick();
    pinNumber("6");
    pinFlag = true;
}


void Pincode::on_B7_clicked()
{
    handleClick();
    pinNumber("7");
    pinFlag = true;
}


void Pincode::on_B8_clicked()
{
    handleClick();
    pinNumber("8");
    pinFlag = true;
}


void Pincode::on_B9_clicked()
{
    handleClick();
    pinNumber("9");
    pinFlag = true;
}


void Pincode::on_BBack_clicked()
{
    handleClick();
    ui->lineEdit->clear();
    pinFlag = false;
}


void Pincode::on_B0_clicked()
{
    handleClick();
    pinNumber("0");
    pinFlag = true;
}


void Pincode::on_BEnter_clicked()
{
    handleClick();
    QString pin = ui->lineEdit->text();
    emit sendPincode(pin);
}

