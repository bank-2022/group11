#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include <QDialog>

namespace Ui {
class TransactionsWindow;
}

class TransactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr);
    ~TransactionsWindow();

    QTimer * transactionsWindowTimer;
    void startTransactionsWindowTimer();
    void reStartTransactionsWindowTimer();

private slots:
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::TransactionsWindow *ui;
};

#endif // TRANSACTIONSWINDOW_H
