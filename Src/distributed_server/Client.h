/*************************************************************************
	> File Name: Client.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月23日 星期一 18时16分42秒
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H
#include "./Buffer.h"
#include <assert.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <map>
class ClientConnect{
public:
    ClientConnect(int fd):fd_(fd){

    }
    ~ClientConnect(){

    }
    int send(int fd){
        //       
    }
    int fd_;
    eylib::Buffer inputBuffer_; //输入Buffer

};
typedef std::shared_ptr<ClientConnect> connectionPtr;
#endif
