/*************************************************************************
	> File Name: Objec_Pool.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 09时28分44秒
 ************************************************************************/

#pragma once 
#include <list>
#include <iostream>
#include <memory>

template <typename T>
class ObjectPool{
public:
    template<typename ...Args>
    ObjectPool(int number,Args ...args):number_(number){
        initObjectPool(args...);
    }
    //获取对象
    T *getObject(void){
        T *ObjectPtr = ObjectPool_.front();
        ObjectPool_.pop_front();
        return ObjectPtr;
    }
    //归还对象.
    void giveBackObject(T *t){
        ObjectPool_.push_back(t);
    }
    //销毁所有对象
    ~ObjectPool(){
        for(auto x:ObjectPool_){
            delete x;
        }
    }
private:
    //初始化对象池
    template<typename  ...Args>
    void initObjectPool(Args ...args){
        for(int i = 0;i < number_;i++){
            ObjectPool_.push_back(new T(args...));
        }
    }
    std::list<T *> ObjectPool_;
    int number_;
};
