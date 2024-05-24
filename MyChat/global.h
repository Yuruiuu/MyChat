#ifndef GLOBAL_H
#define GLOBAL_H


#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
#include <memory>
#include <iostream>
#include <mutex>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

/**
 * @brief repolish 用于刷新qss
 */

extern std::function<void(QWidget*)> repolish;

//requestID
enum ReqId{
    ID_GET_VERIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
};

//模块
enum Modules{
    REGISTERMOD = 0,  //注册模块
};

//错误码
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,  //JSON解析错误
    ERR_NETWORK = 2,  //网络错误
};

#endif // GLOBAL_H
