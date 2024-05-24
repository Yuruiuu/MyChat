#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "Singleton.h"
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>  //.pro中加network


//继承QObject：有信号和槽
//public Singleton<HttpMgr>以自己为基类：CRTP技术支持的
class HttpMgr:public QObject,public Singleton<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();//公有的析构
private:
    friend class Singleton<HttpMgr>;//声明为友元，于是子类可以访问基类的构造函数
    HttpMgr();//单例的构造函数不能是公有的
    QNetworkAccessManager _manager;//管理和发送网络请求
    void PostHttpReq(QUrl url,QJsonObject json,ReqId req_id,Modules mod);
public slots:
    void slot_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod);//槽函数参数个数小于等于信号参数
signals:
    void sig_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod);
    void sig_reg_mod_finish(ReqId id,QString res,ErrorCodes err);
};

#endif // HTTPMGR_H
