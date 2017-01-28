/*************************************************************************
	> File Name: StormDB_Stack.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 17时39分47秒
 ************************************************************************/

#ifndef _STORMDB_STACK_H
#define _STORMDB_STACK_H
#include <iostream>
#include <mutex>
#include <stack>
template <typename T>
class Stack{
private:
    std::stack<T> data; //
    unsigned int size; //
    std::mutex Stackmutex; //
public:
    Stack();
    bool StackIsEmpty();
    void StackPop(); //
    void StackPush(const T &rhs);
    T StackTop();
    unsigned int StackSize();
    void StackDestory();

    Stack& operator = (const Stack& a);
};
template <typename T>
Stack<T>::Stack(){
    size = 0;
}
template <typename T>
bool Stack<T>::StackIsEmpty(){
    while(1){
        if(Stackmutex.try_lock()){
            if(size == 0){
                Stackmutex.unlock();
                return true;
            }else{
                Stackmutex.unlock();
                return false;
            }
        }
    }
}
template <typename T>
void Stack<T>::StackPop(){
    while(1){
        if(Stackmutex.try_lock()){
            if(size == 0){
                Stackmutex.unlock();
                break;
            }
            data.pop();
            std::cout << "t:pop"<<std::endl;
            size--;
            Stackmutex.unlock();
            break;
        }
    }
}
template <typename T>
void Stack<T>::StackPush(const T &rhs){
    while(1){
        if(Stackmutex.try_lock()){
            data.push(rhs);
            size++;
            Stackmutex.unlock();
            break;
        }
    }
}
template <typename T>
T Stack<T>::StackTop(){
    return data.top();
}
template <typename T>
unsigned int Stack<T>::StackSize(){
    while(1){
        if(Stackmutex.try_lock()){
            int  st = size;
            Stackmutex.unlock();
            return st;
        }
    }
}
template <typename T>
void Stack<T>::StackDestory(){
    while(1){
        if(Stackmutex.try_lock()){
            size = 0;
            std::stack<T>().swap(data);
            Stackmutex.unlock();
            break;

        }
    }
}
template <typename T>
Stack<T>& Stack<T>::operator = (const Stack &a){
    size = a.size;
    data = a.data;
    return *this;
}
#endif
