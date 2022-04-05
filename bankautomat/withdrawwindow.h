#ifndef WITHDRAWWINDOW_H
#define WITHDRAWWINDOW_H

#include <QDialog>
#include <iostream>
#include <string>

class MainWindow;

namespace Ui {
class WithdrawWindow;
}

class WithdrawWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawWindow(QWidget *parent = nullptr,MainWindow * ptr = nullptr);
    ~WithdrawWindow();

    void withdrawOtherAmount(QString i);

private slots:
    void on_tenButton_clicked();
    void on_fourtyButton_clicked();
    void on_sixtyButton_clicked();
    void on_hundredButton_clicked();
    void on_twoHundredButton_clicked();
    void on_fiveHundredButton_clicked();

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

    void on_backspaceButton_clicked();
    void on_enterButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::WithdrawWindow *ui;
    MainWindow * pMainWindow;
    QString withdrawAmount;
};

#endif // WITHDRAWWINDOW_H
