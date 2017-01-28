/*************************************************************************
	> File Name: StormDB_Epoll.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月23日 星期一 17时16分24秒
 ************************************************************************/

#ifndef _STORMDB_EPOLL_H
#define _STORMDB_EPOLL_H
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "./ObjectPool.h"
#include <memory>
#include "./Client.h"
#include "./Callback.h"
#define MAXSIZE 1024
#define EPOLLEVENTS 1024
using namespace eylib;
class ClientEpoll{
public:
    ClientEpoll(int fd):eventfd(fd),ObjectPool_(1024,0){
    }
    ~ClientEpoll(){
        close(eventfd);
    }
    void loop();
    void handleRead(int fd);
    void handleClose(int fd);
    void handlewrite(int fd);
    void addReadEvent(int fd);
    void setNonBlocking(int fd);
    void handleEventFdRead(void);
    void setConnectionCallback(ClientconnectionCallback cb){
        clientconnectionCallback_ = cb;
    }
    void setMessageCallback(ClientmessageCallback cb){
        clientmessageCallback_ = cb;
    }
    void setCloseCallback(ClientcloseCallback cb){
        clientcloseCallback_ = cb;
    }
    void setWriteCompleteCallback(ClientwriteCompleteCallback cb){
        clientwriteCompleteCallback_ = cb;
    }
private:
    int eventfd;
    int epollfd;
    typedef std::map<int,std::shared_ptr<ClientConnect>> ConnectionMap;
    struct epoll_event events_[EPOLLEVENTS];
    ConnectionMap connectionMap_;
    ObjectPool<ClientConnect> ObjectPool_;
    ClientmessageCallback clientmessageCallback_;
    ClientcloseCallback clientcloseCallback_;
    ClientconnectionCallback clientconnectionCallback_;
    ClientwriteCompleteCallback clientwriteCompleteCallback_;

}; 
#endif
