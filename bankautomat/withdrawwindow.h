#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include <QDialog>
#include "dllrestapi.h"

class MainMenu;

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr, MainMenu * ptr = nullptr, DLLRestApi *api = nullptr);
    ~WithdrawWindow();

    QTimer * withdrawWindowTimer;
    void startWithdrawWindowTimer();
    void reStartWithdrawWindowTimer();

    QTimer * withdrawWarningTimer;

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);
    void printBalance(QString balance);

    void withdrawOtherAmount(QString i);
    void withdrawMessage(QString message);

    void getCardNumber(QString cardnumber);
    void clearWithdrawWindow();

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

    void on_clearButton_clicked();
    void on_enterButton_clicked();

    void on_exitButton_clicked();

    void warningTimerFinished();
    void getBalance();
    void updateBalance(long long balance);

private:
    Ui::WithdrawWindow *ui;

    MainMenu * pMainMenu;
    DLLRestApi * pRestApi;

    QString withdrawAmount;
    long long withdrawCents;

    QString stringBalance;
    long longCentsBalance;

    QString convertToEuros(long long sum);

    QString cardType;
    QString debitType = "debit";
    QString creditType = "credit";

    QString cardNumber;
    QString accountNum;

    bool withdrawFlag;
};

#endif // WITHDRAWWINDOW_H
