/*************************************************************************
	> File Name: Event_loop.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 10时58分28秒
 ************************************************************************/
#include "Event_loop.h"
#include "Epoll.h"
#include "Connection.h"
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
using namespace eylib;

EventLoop::EventLoop(int eventFd):eventFd_(eventFd),epoll_(new Epoll(1024)),ObjectPool_(1024,0,epoll_){
    //将eventFd_添加到epoll事件表中
    epoll_ -> addFd(eventFd_);
}
EventLoop::~EventLoop(){
    close(eventFd_);
}
void 
EventLoop::loop(){
    while(1){
        int count = epoll_->wait(events_);
        int sockfd;
        for(int i = 0;i < count; i++){
            sockfd = events_[i].data.fd;
            if(sockfd == eventFd_){
                handleEventFdRead();
            }else if(events_[i].events & EPOLLRDHUP){
                //处理关闭
                handleClose(events_[i].data.fd);
            }else if(events_[i].events & EPOLLIN){
                //处理读事件
                handleRead(events_[i].data.fd);
            }else if(events_[i].events & EPOLLOUT){
                //处理可写
            }else if(events_[i].events & EPOLLERR){
                //处理错误
            }
        }
    }
}
void 
EventLoop::handleEventFdRead(void){
    uint64_t fd; //用于保存新的fd
    ssize_t count = read(eventFd_,&fd,sizeof(fd));
    assert(count == sizeof(fd));
    //将新来的套接字添加进epoll时间表中
    epoll_->addFd((int)fd);
    //从连接池中取出新连接,并给智能指针自定义删除器,将连接放回连接池.
    std::shared_ptr<Connection> connecionPtr(ObjectPool_.getObject(),[&](Connection *p){ObjectPool_.giveBackObject(p);});
    connecionPtr->fd_ = fd;
    connectionMap_.insert(std::pair<int,std::shared_ptr<Connection>>(fd,connecionPtr));
    //clientMap.insert(std::pair<std::string,std::shared_ptr<Connection>>
      //               (connecionPtr->ConnectionName_,connecionPtr));
    connectionCallback_(connectionMap_[fd]);

}
void 
EventLoop::handleRead(int fd){
    //printf("handleRead\n");
    //printf("handleRead-->fd: %d\n",fd);
    int count = connectionMap_[fd]->inputBuffer_.readFromFd(fd); //将数据读到该描述符的inputBuffer中.
    int t=count - 4;
   // printf("count =%d\n,head = %d\n",count,connectionMap_[fd]->inputBuffer_.getHeadLength());
    int m = connectionMap_[fd]->inputBuffer_.getHeadLength();
   // printf("t=%d\nm=%d\n",t,m);
    if( t == m ){
    //    printf("哈哈哈!\n");
        messageCallback_(connectionMap_[fd]);//当消息条件满足时调用messageCallback;
    }
    if(count == 0){ //对端关闭
        handleClose(fd);
    }
    //
    //printf("ddddddddd\n");
}
void
EventLoop::handleClose(int fd){
    closeCallback_(connectionMap_[fd]);
}

