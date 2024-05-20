#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QDebug>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置密码输入模式
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);
    //设置和刷新样式
    ui->err_label->setProperty("state","normal");
    repolish(ui->err_label);

    // Print the initial property value
    qDebug() << "Initial state:" << ui->err_label->property("state").toString();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_btn_clicked()
{
    auto mail = ui->pass_lineEdit->text();
    //验证邮箱正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(mail).hasMatch();
    if(match){
        //发送http验证码
    }{
        showTip("邮箱地址不正确",false);
    }
}

void RegisterDialog::showTip(QString str,bool trf)
{

    if(trf){
        ui->err_label->setProperty("state","normal");

    }
    else{
        ui->err_label->setProperty("state","err");
    }

    ui->err_label->setText(str);

    repolish(ui->err_label);
}

