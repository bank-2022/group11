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

#include "restapi.h"

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

public slots:
    void loginSuccessfulSlot();
    void loginFailedSlot(QString message);
    void forbiddenAccessDetected();

private slots:
    void on_mainMenuButton_clicked();

private:
    Ui::MainWindow *ui;
    MainMenu * pMainMenu;
    RestApi * pRestApiInterfaceClass;

    QString cardPin;
    QString cardNumber;



};
#endif // MAINWINDOW_H
