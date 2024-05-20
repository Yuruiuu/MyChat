#include "global.h"


std::function<void(QWidget*)> repolish = [](QWidget* w){
    w->style()->unpolish(w);//去除当前样式
    w->style()->polish(w);//设置新样式
};
