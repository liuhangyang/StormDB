/*************************************************************************
	> File Name: Event_loop.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 10时27分56秒
 ************************************************************************/

#ifndef _EVENT_LOOP_H
#define _EVENT_LOOP_H
#include <memory> 
#include <sys/epoll.h>
#include "Epoll.h"
#include "Connection.h"
#include "ObjectPool.h"
#include "Callback.h"
#include <stdio.h>
#include <map>
namespace eylib{
    class EventLoop{
    public:
        EventLoop(int eventFd);
        ~EventLoop();
        void loop();
        void handleEventFdRead(void);
        void handleRead(int fd);
        void handleClose(int fd);
        void setMessageCallback(messageCallback cb){
            messageCallback_ = cb;
        }
        void setCloseCallback(closeCallback cb){
            closeCallback_ = cb;
        }
        void setWriteCompleteCallback(writeCompleteCallback cb){
            writeCompleteCallback_ = cb;
        }
        void setConnectionCallback(connectionCallback cb){
            connectionCallback_ = cb;
        }
        private:
            typedef std::map<int,std::shared_ptr<Connection>> ConnectionMap;
            
            int eventFd_; //用于主loop向其他loop传递新连接的文件描述符
            std::shared_ptr<Epoll> epoll_; //所拥有的epoll循环
            struct epoll_event events_[1024]; //获取epoll的就绪事件
            messageCallback messageCallback_ ; //消息回调
            closeCallback closeCallback_;//关闭回调
            ObjectPool<Connection> ObjectPool_; //连接池对象
            writeCompleteCallback writeCompleteCallback_; //写完成回调
            connectionCallback connectionCallback_;
            ConnectionMap connectionMap_;
    };
}
#endif
