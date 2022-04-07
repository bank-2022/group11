#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QTimer>

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
    explicit MainMenu(QWidget *parent = nullptr,MainWindow * ptr = nullptr);
    ~MainMenu();

    void startMainMenuTimer();
    void reStartMainMenuTimer();
    QTimer * mainMenuTimer;


private slots:
    void on_withdrawButton_clicked();
    void on_transactionsButton_clicked();
    void on_donateButton_clicked();
    void on_logOutButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::MainMenu *ui;
    MainWindow * pMainWindow;
    DonationWindow * pDonationWindow;
    TransactionsWindow * pTransactionsWindow;
    WithdrawWindow * pWithdrawWindow;
};

#endif // MAINMENU_H
