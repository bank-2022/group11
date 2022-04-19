#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include <QDialog>

#include "restapi.h"

class MainWindow;

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr,MainWindow * ptr = nullptr, RestApi *api = nullptr);
    ~TransactionsWindow();

    QTimer * transactionsWindowTimer;
    void startTransactionsWindowTimer();
    void reStartTransactionsWindowTimer();

    void printName(QString name);
    void printAccountNumber(QString accountNumber);
    void printType(QString type);
    void printBalance(QString balance);

private slots:
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::TransactionsWindow *ui;
    MainWindow * pMainWindow;
    RestApi * pRestApiInterfaceClass;
};

#endif // TRANSACTIONSWINDOW_H
