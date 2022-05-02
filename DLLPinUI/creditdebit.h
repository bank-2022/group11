#ifndef CREDITDEBIT_H
#define CREDITDEBIT_H

#include <QDialog>

namespace Ui {
class CreditDebit;
}

class CreditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDebit(QWidget *parent = nullptr);
    ~CreditDebit();

private:
    Ui::CreditDebit *ui;
};

#endif // CREDITDEBIT_H
