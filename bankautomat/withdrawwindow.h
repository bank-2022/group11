#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include <QDialog>
#include <iostream>
#include <string>

#include "restapi.h"

class MainWindow;

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr, MainWindow * ptr = nullptr, RestApi *api = nullptr);
    ~WithdrawWindow();

    void withdrawOtherAmount(QString i);

    QTimer * withdrawWindowTimer;
    void startWithdrawWindowTimer();
    void reStartWithdrawWindowTimer();

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);
    void printBalance(QString balance);


private slots:
    void on_tenButton_clicked();
    void on_fourtyButton_clicked();
    void on_sixtyButton_clicked();
    void on_hundredButton_clicked();
    void on_twoHundredButton_clicked();
    void on_fiveHundredButton_clicked();

    void on_oneButton_clicked();
    void on_twoButton_clicked();
    void on_threeButton_clicked();
    void on_fourButton_clicked();
    void on_fiveButton_clicked();
    void on_sixButton_clicked();
    void on_sevenButton_clicked();
    void on_eightButton_clicked();
    void on_nineButton_clicked();
    void on_zeroButton_clicked();

    void on_backspaceButton_clicked();
    void on_enterButton_clicked();

    void on_exitButton_clicked();



private:
    Ui::WithdrawWindow *ui;
    QString withdrawAmount;

    MainWindow * pMainWindow;
    RestApi * pRestApiInterfaceClass;
    QString cardType;
};

#endif // WITHDRAWWINDOW_H
