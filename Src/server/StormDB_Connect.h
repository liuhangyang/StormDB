/*************************************************************************
	> File Name: StormDB_Connect.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月25日 星期三 13时56分55秒
 ************************************************************************/

#ifndef _STORMDB_CONNECT_H
#define _STORMDB_CONNECT_H
#include "Buffer.h"
#include <assert.h>
#include <stdio.h>
#include <memory>
#include <string>
class ServerConnect{
public:
    ServerConnect(int fd):fd_(fd){

    }
    ~ServerConnect(){
        
    }
    int send(int fd){
        int ableWrites = outputBuffer_.readableSize();
        std::cout << "senbefore" <<std::endl;
        int writeBytes = outputBuffer_.writeToFd(fd);
        std::cout << "sendafter" <<std::endl;
        return writeBytes;
    }

    int fd_;
    eylib::Buffer inputBuffer_; //输入Buffer;
    eylib::Buffer outputBuffer_; //输出Buffer;
};
#endif
