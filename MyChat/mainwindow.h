#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
/***********************************************
* @file       mainwindow.h
* @brief      主窗口
*
* @author     yuruiuu
* @date       2024/05/18
* @history
************************************************/

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
    void switchToRegister();

private:
    Ui::MainWindow *ui;
    LoginDialog* login_dlg;
    RegisterDialog* reg_dlg;

};
#endif // MAINWINDOW_H
