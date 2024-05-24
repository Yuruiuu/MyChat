#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QDebug>
#include "httpmgr.h"    //非系统头文件尽量包含在cpp里面，防止互引用

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

    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
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

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS){
        showTip("网络请求错误",false);
        return;
    }
    //解析json字符串,res转为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //解析失败
    if(jsonDoc.isNull()){
        showTip("Json解析失败",false);
        return;
    }
    //解析错误
    if(!jsonDoc.isObject()){
        showTip("Json解析失败",false);
        return;
    }

    //回调函数
    _handlers[id](jsonDoc.object());

    return;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this](const QJsonObject& jsonOb){
       int error =  jsonOb["error"].toInt();
       if(error!=ErrorCodes::SUCCESS){
           showTip("参数错误",false);
           return;
       }

       auto email = jsonOb["email"].toString();
       showTip("验证码已发送至邮箱，注意查收",true);
       qDebug()<<"email is : "<<email;
    });
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

