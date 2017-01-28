/********mZ****************************************************************
	> File Name: Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 14时45分50秒
 ************************************************************************/

#include "Server.h"
#include <memory>
#include <string>
using namespace eylib;
Server::Server(std::string ip,int port,int loopNumber)
    :baseLoopPtr_(std::make_shared<BaseLoop>(ip,port,loopNumber)){

}
Server::~Server(){
}
void 
Server::start(){
    baseLoopPtr_ -> setConnectionCallback(connectionCallback_); //设置连接回调
    baseLoopPtr_ -> setMessageCallback(messageCallback_); //设置读回调函数
    baseLoopPtr_ -> setCloseCallback(closeCallback_); //设置关闭回调函数
    baseLoopPtr_ -> setWriteCompleteCallback(writeCompleteCallback_); 
    baseLoopPtr_ -> start();
}
