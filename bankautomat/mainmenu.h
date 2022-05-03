#ifndef MAINMENU_H
#define MAINMENU_H

#include <QVector>
#include <QStandardItemModel>
#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <cmath>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <stdio.h>

#include <qstylefactory.h>

#include "dllrestapi.h"

#include "donationwindow.h"
#include "transactionswindow.h"
#include "withdrawwindow.h"

class MainWindow;

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr, MainWindow *ptr = nullptr, DLLRestApi *api = nullptr);
    ~MainMenu();


    void startMainMenuTimer();
    void reStartMainMenuTimer();

    void printName(QString name);
    void printAccountNumber(QString accountNum);
    void printType(QString type);
    void printBalance(QString balance);
    void print5Transactions(QString accountNum);

    void getCardNumber(QString cardnumber);
    void getAccountNumber(QString accountNum);

    void clearMainMenuWindow();

private slots:
    void on_withdrawButton_clicked();
    void on_transactionsButton_clicked();
    void on_donateButton_clicked();
    void on_logOutButton_clicked();
    void updateBalance(long long balance);
    void update5List(QVector<QVector<QString>> list);
    void updateTransactions();

private:
    Ui::MainMenu *ui;

    MainWindow * pMainWindow;
    DLLRestApi * pRestApi;
    DonationWindow * pDonationWindow;
    TransactionsWindow * pTransactionsWindow;
    WithdrawWindow * pWithdrawWindow;

    QString convertToEuros(long long sum);

    QString accountNumber;
    QString cardNumber;

    QTimer * mainMenuTimer;
};

#endif // MAINMENU_H
