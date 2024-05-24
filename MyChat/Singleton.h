#ifndef SINGLETON_H
#define SINGLETON_H

#include<global.h>

//单例类
//将其设计为基类
template <typename T>
class Singleton{
protected:
    Singleton() = default;//保护的构造，子类可以调用
    Singleton(const Singleton<T>&) = delete;//单例不允许被拷贝构造和拷贝赋值，所以把默认的函数删除。
    Singleton& operator = (const Singleton<T>&) = delete;
    static std::shared_ptr<T> _instance;//static指针：使所有singleton都返回同一个实例
public:
    //static函数：可以通过类名直接调用函数
    //std::call_once 和 std::once_flag确保无论多少线程同时调用 GetInstance函数，_instance只会被初始化一次。
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[&](){
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress(){
        std::cout<<_instance.get()<<std::endl;
    }

    ~Singleton(){
        std::cout<<"singleton destruct"<<std::endl;
    }
};

//static类型的变量一定要初始化
//因为是模板类，所以在.h里初始化
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
