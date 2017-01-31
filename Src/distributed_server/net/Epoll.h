/*************************************************************************
	> File Name: Epoll.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 22时09分20秒
 ************************************************************************/

#ifndef _EPOLL_H
#define _EPOLL_H
#include <sys/epoll.h>
namespace eylib{
    class Epoll{
    public:
        Epoll(int epollSize);
        ~Epoll();
        void setNonBlocking(int fd); //将套接字描述符设置为非阻塞的.
        void addFd(int fd); //向epoll内核事件表添加所对应的事件修改
        void modFd(int fd,int events); //将内核中某个套接字所对应的事件修改.
        void delFd(int fd); //将epoll事件表中的某个事件删除.
        int wait(struct epoll_event *events);
    private:
        int epollSize_; //epoll内核事件表的大小.
        int epollFd_; //epoll内核事件表的描述符.
        int maxEvents_;  //epoll_wait最多监听的事件个数. 
    };
}
#endif
