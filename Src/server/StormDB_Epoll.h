/*************************************************************************
	> File Name: StormDB_Epoll.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月25日 星期三 12时43分42秒
 ************************************************************************/

#ifndef _STORMDB_EPOLL_H
#define _STORMDB_EPOLL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define IP "127.0.0.1"
#define PORT 10000
#include "./StormDB_Connect.h"
#include "./StormDB_Callback.h"
class ServerEpoll{
public:
    ServerEpoll()=default;
    ~ServerEpoll(){
        close(epollfd);
    }
    int  init(const char* ip,int port);
    void loop();
    void handleRead(int fd);
    void handleClose(int fd);
    void handleWrite(int fd);
    void addReadEvent(int fd);
    void addWriteEvent(int fd);
    void delWriteEvent(int fd);
    
    void setNonBlocking(int fd);
    void handleAccept(int fd);
    
    void setServerConnectCallback(ServerConnectCallback cb){
        serverConnectCallback_ = cb;
    }
    void setServerMessageCallback(ServerMessageCallback cb){
        serverMessageCallback_ = cb;
    }
    void setServerCloseCallback(ServerCloseCallback cb){
        serverCloseCallback_ = cb;
    }
    void setServerWriteCallback(ServerWriteCallback cb){
        serverWriteCallback_ = cb;
    }
private:
    struct sockaddr_in serveraddr;
    int epollfd;
    struct epoll_event events_[1024];
    std::shared_ptr<ServerConnect> conn;  //伪客户端的连接
    ServerConnectCallback serverConnectCallback_;
    ServerMessageCallback serverMessageCallback_;
    ServerCloseCallback serverCloseCallback_;
    ServerWriteCallback serverWriteCallback_;
};
#endif

