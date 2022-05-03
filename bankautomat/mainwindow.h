#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QTimer>

#include <QVector>
#include <QStandardItemModel>
#include <QDebug>
#include <cmath>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "dllrestapi.h"
#include "dllserialport.h"
#include "dllpinui.h"

#include "mainmenu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString name;
    QString accountNumber;

public slots:
    void loginSuccessfulSlot();
    void loginFailedSlot(QString message);
    void forbiddenAccessDetected();

private slots:
    void receivePincode(QString pin);
    void getCustomerInfo();
    void updateCustomerInfo(QVector<QString> info);
    void getCustomerType();
    void updateType(QString type);
    void updateBalance(long long balance);
    void get5Transactions();

    void receiveCardNumber(QString);
    void showMainMenu();

    // these are for testing
    void on_ruusuButton_clicked();
    void on_olaviButton_clicked();
    void on_failLoginButton_clicked();

private:
    Ui::MainWindow *ui;
    MainMenu * pMainMenu;
    DLLRestApi * pRestApi;
    DLLSerialPort * pSerialPort;
    DLLPinUI * pPinUI;

    QString cardPin;
    QString cardNumber;

    QString convertToEuros(long long sum);

};
#endif // MAINWINDOW_H
