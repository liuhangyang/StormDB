/*************************************************************************
	> File Name: Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月26日 星期四 10时24分49秒
 ************************************************************************/

#include<iostream>
#include "./Server.h"
#include <stdio.h>
using namespace std;
void serverMessage(std::shared_ptr<ServerConnect> p,int m){
    /*char buf[1024];
    p->inputBuffer_.getData(buf,m);
    printf("buf:%s\n",buf);
    printf("nhnbnbchdbchdcd\n");*/
    Task task(p,server->returnDB(),m);
    printf("huhuhuh\n");
    pool.AddTask(task);
    printf("add\n");
}
void serverConnect(std::shared_ptr<ServerConnect> p){
    
}
void serverClose(std::shared_ptr<ServerConnect> p){
    close(p->fd_);
}
void serverWrite(std::shared_ptr<ServerConnect> p){
    
}
int main(int argc,char *argv[])
{
    server->setServerConnectCallback(serverConnect);
    server->setServerMessageCallback(serverMessage);
    server->setServerCloseCallback(serverClose);
    server->setServerWriteCallback(serverWrite);
    server->Start();
   return 0;
}
