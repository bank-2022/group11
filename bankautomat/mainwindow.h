#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>

#include "donationwindow.h"
#include "transactionswindow.h"
#include "withdrawwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_withdrawButton_clicked();
    void on_viewTransactionsButton_clicked();
    void on_donateButton_clicked();
    void on_logOutButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    DonationWindow * pDonationWindow;
    TransactionsWindow * pTransactionsWindow;
    WithdrawWindow * pWithdrawWindow;
};
#endif // MAINWINDOW_H
