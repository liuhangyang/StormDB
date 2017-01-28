/*************************************************************************
	> File Name: Base_loop.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 22时55分51秒
 ************************************************************************/
#include "Base_loop.h"
#include <string>
#include "Event_loop_thread_pool.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <memory>
using namespace eylib;
BaseLoop::BaseLoop(std::string ip,int port,int loopNumber):ip_(ip),port_(port),loopThreadPoolPtr_(std::make_shared<LoopThreadPool>(loopNumber)){}
BaseLoop::~BaseLoop(){
    close(listenFd_);
}
int BaseLoop::createListenFd(void){
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip_.c_str(),&address.sin_addr);
    address.sin_port = htons(port_);
    
    int sock = socket(PF_INET,SOCK_STREAM,0);
    printf("sockFd:%d\n",sock);
    assert(sock >= 0);

    int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
    assert(sock >= 0);

    ret = listen(sock,100);
    assert(ret == 0);
    return sock;
}
void
BaseLoop::start(void){
    struct sockaddr_in clientAddress; //保存客户端地址
    socklen_t len = sizeof(clientAddress); //客户端地址长度
    int connfd;
    listenFd_ = createListenFd(); //获得监听套接字
    loopThreadPoolPtr_ -> setMessageCallback(messageCallback_); //设置读回调函数
    loopThreadPoolPtr_ -> setCloseCallback(closeCallback_); //设置关闭回调函数
    loopThreadPoolPtr_ -> setWriteCompleteCallback(writeCompleteCallback_);
    loopThreadPoolPtr_ -> setConnectionCallback(connectionCallback_);
    loopThreadPoolPtr_ -> start(); //开启loop线程池
    //主线程负责accpet新的连接,接收到连接后就注册到event_loop_thread_pool里.
    while(1){
        connfd = accept(listenFd_,(struct sockaddr *)&clientAddress,&len);
        printf("connfd:%d\n",connfd);
        connectionHandle(connfd);
    }
}
void
BaseLoop::connectionHandle(int connfd){
    int fd = loopThreadPoolPtr_ -> getNextLoop();
    printf("loopfd:%d\n",fd);
    uint64_t buff = connfd;
    int ret = write(fd,&buff,sizeof(buff)); //添加到指定的loop循环中.
    assert(ret == sizeof(buff));
}
