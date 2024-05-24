#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_btn_clicked();
    void slot_reg_mod_finish(ReqId,QString,ErrorCodes);
private:
    void initHttpHandlers();
    void showTip(QString,bool);
    Ui::RegisterDialog *ui;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;//通过id区分，处理很多的http请求
};

#endif // REGISTERDIALOG_H
