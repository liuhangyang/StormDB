/*************************************************************************
	> File Name: StormDB_Epoll.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月23日 星期一 19时01分16秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Epoll.h"
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <stdio.h>
using namespace std;

void
ClientEpoll::loop(){
    epollfd = epoll_create(EPOLLEVENTS);
    while(1){
        addReadEvent(eventfd);
        int sockfd;
        int count = epoll_wait(epollfd,events_,EPOLLEVENTS,-1);
        //printf("count:%d\n",count);
        for(int i = 0;i < count;i++){
            sockfd = events_[i].data.fd;
            if(sockfd == eventfd){
                handleEventFdRead();
            }
            else if(events_[i].events & EPOLLRDHUP){
                //处理关闭
                handleClose(events_[i].data.fd);
            }else if(events_[i].events & EPOLLIN){
                //处理读事件
                handleRead(events_[i].data.fd);
            }else if(events_[i].events & EPOLLOUT){
                //处理写事件
                handlewrite(events_[i].data.fd);
            }
        }
    }
}
void 
ClientEpoll::handleClose(int fd){
   clientcloseCallback_(connectionMap_[fd]);
}
void
ClientEpoll::handleRead(int fd){
    int count = connectionMap_[fd]->inputBuffer_.readFromFd(fd);
    int t =count -4;
    int m = connectionMap_[fd] -> inputBuffer_.getHeadLength();
    std::cout << " t:----> " << t << "m------->" <<m <<std::endl;
    if(t == m){
        clientmessageCallback_(connectionMap_[fd],m);

    }
    if(count == 0){
        handleClose(fd);
    }
}
void
ClientEpoll::handlewrite(int fd){
    
}
void 
ClientEpoll::addReadEvent(int fd){
    printf("fd=%d\n",fd);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
    setNonBlocking(fd);
}
void
ClientEpoll::handleEventFdRead(void){
    uint64_t fd;
    printf("eventfd:%d\n",eventfd);
    ssize_t count = read(eventfd,&fd,sizeof(fd));
    assert(count == sizeof(fd));
    addReadEvent((int)fd);
    std::shared_ptr<ClientConnect> connectionPtr(ObjectPool_.getObject(),[&](ClientConnect * p){ObjectPool_.giveBackObject(p);});
    connectionPtr->fd_= fd;
    printf("fd --------->:%d\n",fd);
    connectionMap_.insert(std::pair<int,std::shared_ptr<ClientConnect>>(fd,connectionPtr));
    
}
void 
ClientEpoll::setNonBlocking(int fd){
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
/*
int main(int argc,char *argv[])
{
   return 0;
}*/
