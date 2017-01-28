/*************************************************************************
	> File Name: StormDB_Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月26日 星期四 09时22分25秒
 ************************************************************************/

#include<iostream>
#include <functional>
#include <memory>
#include "./StormDB_Server.h"
void
StormDBServer::Start(){
    serverepoll->setServerConnectCallback(getServerConnectCallback());
    serverepoll->setServerMessageCallback(getServerMessageCallback());
    serverepoll->setServerCloseCallback(getServerCloseCallback());
    serverepoll->setServerWriteCallback(getServerWriteCallback());
    serverepoll->loop();
}
