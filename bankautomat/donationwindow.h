#ifndef DONATIONWINDOW_H
#define DONATIONWINDOW_H

#include <QDialog>
class MainWindow;

namespace Ui {
class DonationWindow;
}

class DonationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DonationWindow(QWidget *parent = nullptr,MainWindow * ptr = nullptr);
    ~DonationWindow();

    void donateOtherAmount(QString i);
    QTimer * donationWindowTimer;

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

    void on_exitButton_clicked();

private:
    Ui::DonationWindow *ui;
    MainWindow * pMainWindow;
    QString donationAmount;
};

#endif // DONATIONWINDOW_H
