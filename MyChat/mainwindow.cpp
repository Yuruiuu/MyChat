#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    login_dlg = new LoginDialog(this);
    setCentralWidget(login_dlg);
    //login_dlg->show();

    //处理注册操作
    connect(login_dlg,&LoginDialog::switchToRegister,this,&MainWindow::switchToRegister);

    reg_dlg = new RegisterDialog(this);

    //设置无边框窗口
    login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    reg_dlg->hide();

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::switchToRegister()
{
    setCentralWidget(reg_dlg);
    login_dlg->hide();
    reg_dlg->show();
}

