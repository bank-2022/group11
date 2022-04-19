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

#include "restapi.h"

#include "donationwindow.h"
#include "transactionswindow.h"
#include "withdrawwindow.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr,MainWindow * ptr = nullptr, RestApi *api = nullptr);
    ~MainMenu();

    QTimer * mainMenuTimer;
    void startMainMenuTimer();
    void reStartMainMenuTimer();

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);

public slots:


private slots:
    void on_withdrawButton_clicked();
    void on_transactionsButton_clicked();
    void on_donateButton_clicked();
    void on_logOutButton_clicked();
    void on_refreshButton_clicked();

    //void getCustomerInfo();
    //void updateCustomerInfo(QVector<QString> info);
    void updateBalance(long long balance);
    void updateList(QVector<QVector<QString>> list);





private:
    Ui::MainMenu *ui;

    MainWindow * pMainWindow;
    DonationWindow * pDonationWindow;
    TransactionsWindow * pTransactionsWindow;
    WithdrawWindow * pWithdrawWindow;

    RestApi * pRestApiInterfaceClass;

    QString convertToEuros(long long sum);


};

#endif // MAINMENU_H
