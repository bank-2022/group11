#ifndef PINCODE_H
#define PINCODE_H

#include <QDialog>
#include <QDebug>
#include <QTimer>

namespace Ui {
class Pincode;
}

class Pincode : public QDialog
{
    Q_OBJECT

public:
    explicit Pincode(QWidget *parent = nullptr);
    ~Pincode();
    void pinNumber(QString x);
    void loginSuccessful();
    void loginFailed(QString message);
    void startPincodeTimer();
    void restartPincodeTimer();

signals:
    void sendPincode(QString pin);
    void getType();

private slots:
    void on_B1_clicked();

    void on_B2_clicked();

    void on_B3_clicked();

    void on_B4_clicked();

    void on_B5_clicked();

    void on_B6_clicked();

    void on_B7_clicked();

    void on_B8_clicked();

    void on_B9_clicked();

    void on_BBack_clicked();

    void on_B0_clicked();

    void on_BEnter_clicked();

private:
    Ui::Pincode *ui;
    QVector<QPushButton *> napit;
    short i;
    QString pin;
    bool pinFlag;
    short loginAttempts;
    bool locked;
    QTimer * pincodeTimer;
};

#endif // PINCODE_H
