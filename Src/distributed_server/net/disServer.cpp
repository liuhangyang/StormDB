/*************************************************************************
	> File Name: test_Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 15时00分36秒
 ************************************************************************/

#include "./disServer.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
using namespace eylib;
void messagecallback(std::shared_ptr<eylib::Connection> p){
    
    printf("有数据了!");
}
void  connectioncallback(std::shared_ptr<eylib::Connection> p){
        std::string str("Client_");
        getClientId(str);
        p->ConnectionName_ = str;
        addClient(p);
}
void  closecallback(std::shared_ptr<eylib::Connection> p){
    std::cout << "客户端: " <<p->ConnectionName_<<"关闭了!" <<std::endl;
    close(p->fd_);
}
void  addClient(std::shared_ptr<eylib::Connection> p){
    clientMap.insert(std::pair<std::string,std::shared_ptr<eylib::Connection>>(p->ConnectionName_,p));
    std::cout << "clientMap[p->ConnectionName_]:" <<p->ConnectionName_<<std::endl;
}
void  delClient(std::string str){
    
}
std::shared_ptr<eylib::Connection>  findClient(std::string str){
    
}
int main(int argc,char *argv[])
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;
    Server loop(argv[1],atoi(argv[2]),4);
    loop.setMessageCallback(messagecallback);
    loop.setConnectionCallback(connectioncallback);
    loop.setCloseCallback(closecallback);
    loop.start();
   return 0;
}
