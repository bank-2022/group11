#ifndef DONATIONWINDOW_H
#define DONATIONWINDOW_H

#include <QDialog>
#include "restapi.h"

class MainMenu;

namespace Ui {
class DonationWindow;
}

class DonationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DonationWindow(QWidget *parent = nullptr, MainMenu *ptr = nullptr, RestApi *api = nullptr);
    ~DonationWindow();

    QTimer * donationWindowTimer;
    void startDonationWindowTimer();
    void reStartDonationWindowTimer();

    QTimer * donationWarningTimer;

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);
    void printBalance(QString balance);

    void donateOtherAmount(QString i);
    void donateMessage(QString message);

private slots:
    void on_tenButton_clicked();
    void on_twentyButton_clicked();
    void on_fiftyButton_clicked();
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

    void on_cancelButton_clicked();
    void on_enterButton_clicked();

    void on_exitButton_clicked();

    void warningTimerFinished();

private:
    Ui::DonationWindow *ui;

    MainMenu * pMainMenu;
    RestApi * pRestApiInterfaceClass;

    QString donationAmount;
    long long donationCents;

    QString stringBalance;
    long longCentsBalance;

    QString charityAccount = "FI4265431234000012";

    QString cardType;
    QString debitType = "debit";
    QString creditType = "credit";

    QString cardNumber = "66778899"; // This will be changed when the pin ui dll is ready.
};

#endif // DONATIONWINDOW_H
