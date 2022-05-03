#ifndef CREDITDEBIT_H
#define CREDITDEBIT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class CreditDebit;
}

class CreditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDebit(QWidget *parent = nullptr);
    ~CreditDebit();
    void startCreditDebitTimer();

private slots:
    void on_CreditButton_clicked();

    void on_DebitButton_clicked();

signals:
    void creditDebitSignal(QString choice);

private:
    Ui::CreditDebit *ui;
    QTimer * creditDebitTimer;
};

#endif // CREDITDEBIT_H
