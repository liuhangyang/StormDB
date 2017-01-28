/*************************************************************************
	> File Name: StormDB_Queue.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 14时12分00秒
 ************************************************************************/

#ifndef _STORMDB_QUEUE_H
#define _STORMDB_QUEUE_H
#include <iostream>
#include <mutex>
#include <queue>
template <typename T>
class Queue{
private:
    std::queue<T> data; //队列数据对象
    std::mutex Queuemutex; //队列类中的锁
    unsigned int size;  //队列中对象的个数
public:
    Queue(); //构造函数
    bool QueueIsEmpty(); //判断队列是否为空
    void QueuePop();     //出队,从队列中删除
    T QueueFront(); //读取队首元素
    T QueueBack(); //读取队尾元素
    void QueuePush(const T &rhs); //向队列中添加元素
    unsigned int QueueSize(); //返回队列元素个数
    void QueueDestory();

    Queue& operator=(const Queue &a);
};
template <typename T>
Queue<T>::Queue(){
    size = 0;
}
template <typename T>
bool Queue<T>::QueueIsEmpty(){
    while(1){
        if(Queuemutex.try_lock()){
            if(size == 0){
                Queuemutex.unlock();
                return true;
            }else{
                Queuemutex.unlock();
                return false;
            }
        }
    }
}
template <typename T>
void Queue<T>::QueuePop(){
    while(1){
        if(Queuemutex.try_lock()){
            if(size == 0){
                Queuemutex.unlock();
                break;
            }
            data.pop();
            size--;
            Queuemutex.unlock();
            break;
        }
    }
}
template <typename T>
T Queue<T>::QueueFront(){
    while(1){
        if(Queuemutex.try_lock()){
            T tr = data.front();
            Queuemutex.unlock();
            return tr;
        }
    }
}
template <typename T>
T Queue<T>::QueueBack(){
    while(1){
        if(Queuemutex.try_lock()){
            T tr = data.back();
            Queuemutex.unlock();
            return tr;
        }
    }
}
template <typename T>
void Queue<T>::QueuePush(const T &rhs){
    while(1){
        if(Queuemutex.try_lock()){
            data.push(rhs);
            size++;
            Queuemutex.unlock();
            break;
        }
    }
}
template <typename T>
unsigned int Queue<T>::QueueSize(){
    while(1){
        if(Queuemutex.try_lock()){
            int st = size;
            Queuemutex.unlock();
            return st;
        }
    }
}
template <typename T>
void Queue<T>::QueueDestory(){
    while(1){
        if(Queuemutex.try_lock()){
            size = 0;
            std::queue<T>().swap(data);
            Queuemutex.unlock();
            break;
        }
    }
}
template <typename T>
Queue<T>& Queue<T>::operator = (const Queue<T> &a){
    size = a.size;
    data = a.data;
    return *this;
}
#endif
