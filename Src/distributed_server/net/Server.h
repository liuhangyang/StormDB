/*************************************************************************
	> File Name: Server.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 13时38分00秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include "Base_loop.h"
#include <memory>
#include <string>
#include "Callback.h"
namespace eylib{
    class Server{
    public:
        Server(std::string ip,int port,int loopNumber);
        ~Server();
        void start(void); //开始运行Server
        void setConnectionCallback(connectionCallback cb){
            connectionCallback_ = cb;
        }
        void setMessageCallback(messageCallback cb){
           messageCallback_ =  cb; 
        }
        void setCloseCallback(closeCallback cb){
            closeCallback_ = cb;
        }
        void setWriteCompleteCallback(writeCompleteCallback cb){
            writeCompleteCallback_ = cb;
        }
    private:
        std::shared_ptr<BaseLoop> baseLoopPtr_; //保存baseLoop[]
        connectionCallback connectionCallback_; //连接回调
        messageCallback messageCallback_; //消息回调
        closeCallback closeCallback_; //关闭回调
        
        writeCompleteCallback writeCompleteCallback_;//写完回调.
    };
}
#endif
