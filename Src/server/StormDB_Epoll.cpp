/*************************************************************************
	> File Name: StormDB_Epoll.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月25日 星期三 14时35分40秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Epoll.h"
using namespace std;
void 
ServerEpoll::setNonBlocking(int fd){
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
}
void 
ServerEpoll::addReadEvent(int fd){
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
void 
ServerEpoll::addWriteEvent(int fd){
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLOUT;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
}
void
ServerEpoll::delWriteEvent(int fd){
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}
int 
ServerEpoll::init(const char* ip,int port){
    int listenfd;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd == -1){
        perror("socket error\n");
        exit(1);
    }
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);
    if(bind(listenfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == -1){
        perror("bind error\n");
        exit(1);
    }
    listen(listenfd,1024);
    return listenfd;
}
void 
ServerEpoll::handleRead(int fd){
    int count = conn->inputBuffer_.readFromFd(fd);
    int t = count -4;
    int m = conn->inputBuffer_.getHeadLength();
    std::cout << "count: " << count << "m:"<< m<<std::endl;
    if( t  == m ){
        serverMessageCallback_(conn,m);
    }
    if(count == 0){
        handleClose(fd);
    }
}
void
ServerEpoll::handleWrite(int fd){
    serverWriteCallback_(conn);
}
void 
ServerEpoll::handleClose(int fd){
    serverCloseCallback_(conn);
}
void 
ServerEpoll::handleAccept(int fd){
    socklen_t len =sizeof(serveraddr);
    int connfd = accept(fd,(struct sockaddr*)&serveraddr,&len);
    conn = std::shared_ptr<ServerConnect>(new ServerConnect(connfd));
    addReadEvent(connfd);
}
void 
ServerEpoll::loop(){
   int ret;
    int fd = init(IP,PORT);
   epollfd = epoll_create1(0);
    addReadEvent(fd);
    setNonBlocking(fd);
    for(;;){
        ret = epoll_wait(epollfd,events_,1024,-1);
        for(int i = 0;i<ret;i++){
            int  sockfd = events_[i].data.fd;
            if(sockfd == fd){
                handleAccept(sockfd); 
            }else if(events_[i].events & EPOLLRDHUP){
                handleClose(events_[i].data.fd);
            }else if(events_[i].events & EPOLLIN){
                handleRead(events_[i].data.fd);
            }else if(events_[i].events & EPOLLOUT){
                handleWrite(events_[i].data.fd);
            }
        }
    }

}
