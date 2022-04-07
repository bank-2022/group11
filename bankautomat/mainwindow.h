#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QTimer>

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

    void startTimer();
    void reStartTimer();
    QTimer * mainWindowTimer;


private slots:
    void on_mainMenuButton_clicked();

private:
    Ui::MainWindow *ui;
    MainMenu * pMainMenu;


};
#endif // MAINWINDOW_H
