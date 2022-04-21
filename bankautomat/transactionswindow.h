#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "restapi.h"

class MainMenu;



namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr, MainMenu *ptr = nullptr, RestApi *api = nullptr);
    ~TransactionsWindow();

    QTimer * transactionsWindowTimer;
    void startTransactionsWindowTimer();
    void reStartTransactionsWindowTimer();

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);
    void printBalance(QString balance);
    void showTransactions(QString accountNumber);

private slots:
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_exitButton_clicked();
    void updateList(QVector<QVector<QString>> list);

private:
    Ui::TransactionsWindow *ui;
    MainMenu * pMainMenu;
    RestApi * pRestApiInterfaceClass;
};

#endif // TRANSACTIONSWINDOW_H
