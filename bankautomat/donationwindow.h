#ifndef DONATIONWINDOW_H
#define DONATIONWINDOW_H

#include <QDialog>

namespace Ui {
class DonationWindow;
}

class DonationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DonationWindow(QWidget *parent = nullptr);
    ~DonationWindow();

private slots:
    void on_tenButton_clicked();
    void on_twentyButton_clicked();
    void on_fiftyButton_clicked();
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
    void on_cancelButton_clicked();
    void on_enterButton_clicked();

private:
    Ui::DonationWindow *ui;
};

#endif // DONATIONWINDOW_H
