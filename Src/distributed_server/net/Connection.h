/*************************************************************************
	> File Name: Connection.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 10时06分27秒
 ************************************************************************/

#ifndef _CONNECTION_H
#define _CONNECTION_H
#include "Buffer.h"
#include "Epoll.h"

#include <assert.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <map>
namespace eylib{
    class Connection{
    public:
        int fd_;
        std::string ConnectionName_; //连接的名字
        Buffer inputBuffer_;  //输入Buffer
        Buffer outputBuffer_; //输出Buffer
        std::shared_ptr<Epoll> epoll_; //该连接所运行的epoll
    public:
        Connection(int fd,std::shared_ptr<Epoll> epoll):fd_(fd),epoll_(epoll){
            
        }
        ~Connection(){

        }
        //发送数据
        int send(void){
            //可写的字节数
            int ableWrites = outputBuffer_.readableSize();
            int writeBytes = outputBuffer_.writeToFd(fd_);
            //已写的字节数小于buffer中可写的字节数,则说明内核的发送缓冲区已写满
            if(writeBytes < 0){
                printf("发送数据出错\n");
            }else if(writeBytes < ableWrites){
                registerWriteEvent();
            }else if(writeBytes == ableWrites){
                deleteWriteEvent();
            }
            return writeBytes;
        }
        void registerWriteEvent(void){
            int events = EPOLLIN | EPOLLOUT;
            epoll_ -> modFd(fd_,events);
        }
        //删除写事件
        void deleteWriteEvent(void){
            int events = EPOLLIN;
            epoll_ -> modFd(fd_,events);
        }
    };
    typedef std::shared_ptr<Connection> connectionPtr;
    
}


#endif
