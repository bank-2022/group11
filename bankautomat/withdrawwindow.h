#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include <QDialog>
#include "restapi.h"

class MainMenu;

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr, MainMenu * ptr = nullptr, RestApi *api = nullptr);
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

    void warningTimerFinished();

private:
    Ui::WithdrawWindow *ui;

    MainMenu * pMainMenu;
    RestApi * pRestApiInterfaceClass;

    QString withdrawAmount;
    long long withdrawCents;

    QString stringBalance;
    long longCentsBalance;

    QString cardType;
    QString debitType = "debit";
    QString creditType = "credit";

    QString cardNumber = "66778899"; // This will be changed when the pin ui dll is ready.
};

#endif // WITHDRAWWINDOW_H
