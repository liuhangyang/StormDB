/*************************************************************************
	> File Name: test_StormDB_StackQueue.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 18时14分52秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Queue.h"
#include "../StormDB_Stack.h"
using namespace std;
int main(int argc,char *argv[])
{
    Queue<int> Q;
    if(Q.QueueIsEmpty() == true){
        cout << "empty" << endl;
    }
    /*Q.QueuePop();
    cout << Q.QueueFront() << endl;
    cout << "yanglongfei"<<endl;
    cout << Q.QueueBack() <<endl;
    cout << Q.QueueSize() <<endl;*/
    
    Q.QueuePush(1);
    Q.QueuePush(2);
    Q.QueuePush(3);
    Q.QueuePop();
    cout << Q.QueueFront() << endl;
    cout << Q.QueueBack() << endl;
    cout << Q.QueueSize() <<endl;

    Stack<int> S;
    if(S.StackIsEmpty()==true){
        cout << "empty" <<endl;
    }
    S.StackPop();
    cout <<S.StackSize()<<endl;
    S.StackPush(1);
    S.StackPush(2);
    S.StackPush(3);
    cout <<S.StackTop()<<endl;
    cout << S.StackSize()<<endl;
    
   return 0;
}
