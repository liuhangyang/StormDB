/*************************************************************************
	> File Name: Event_loop_thread_pool.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 12时02分51秒
 ************************************************************************/
#include "Event_loop_thread_pool.h"
#include "Event_loop.h"
#include <assert.h>
#include <sys/eventfd.h>
#include <thread>
#include <map>
#include <memory>
#include <functional>
#include <stdio.h>
using namespace eylib;

LoopThreadPool::LoopThreadPool(int number):loopNumber_(number){
    next_ = 1;
}
LoopThreadPool::~LoopThreadPool(){
    for(auto t : threadVector_){ //回收线程
        t->join();
    }
}
int 
LoopThreadPool::getNextLoop(){
    int  fd = fdMap_[next_]; //获取接下来要接受任务的loop的eventfd;
    if(next_ == loopNumber_){
        next_ = 1; //再次回到第一个循环
    }else{
        next_ ++;
    }
    return fd;
}
void LoopThreadPool::start(){
    int fd;
    for(int i = 1;i <= loopNumber_;++i){
        fd = createEventFd();
        printf("LoopThreadPool:fd::%d\n",fd);
        fdMap_.insert(std::pair<int,int>(i,fd)); //将编号及对应的fd存入map;
        threadVector_.push_back(std::make_shared<std::thread>(threadFunc,fd,this));//将新创建的线程对象加入容器中.
    }
}
int LoopThreadPool::createEventFd(){
    int fd = eventfd(0,EFD_NONBLOCK);
    assert(fd > 0);
    return fd;
}
void 
LoopThreadPool::threadFunc(int eventFd,LoopThreadPool *loopThreadPool){
    EventLoop loop(eventFd);
    loop.setMessageCallback(loopThreadPool->getMessageCallback()); //设置消息回调
    loop.setCloseCallback(loopThreadPool->getCloseCallback());//设置关闭回调.
    loop.setWriteCompleteCallback(loopThreadPool->getWriteCompleteCallback()); //设置写完成事件.
    loop.setConnectionCallback(loopThreadPool->getConnectionCallback());
    loop.loop(); //启动循环
}
void
LoopThreadPool::fun(void){
    printf("读时间发生\n");
}
