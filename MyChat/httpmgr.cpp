#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    //伪闭包，C++没有闭包
    auto self = shared_from_this();//获取当前对象的 shared_ptr，确保在lambda表达式中可以安全地使用当前对象。
    QNetworkReply* reply = _manager.post(request,data);//Qt的http是异步的，发送之后不能立即得到结果
    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        //处理错误情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            return;
        }
        //无错误
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;
    });

}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块的http相应结束了
        emit sig_reg_mod_finish(id,res,err);
    }
}
