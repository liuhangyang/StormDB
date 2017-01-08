/*************************************************************************
	> File Name: test_Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 15时00分36秒
 ************************************************************************/

#include <sys/eventfd.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "../Server.h"
#include <functional>
#include <thread>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include "../Connection.h"
#include <memory>
using namespace eylib;
int fd;
uint64_t buffer;
void func(std::shared_ptr<eylib::Connection> p){
    printf("fd = %d\n",p->fd_);
}
int main(int argc,char *argv[])
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;

    Server loop(argv[1],atoi(argv[2]),4);
    loop.setMessageCallback(func);
    loop.start();
   return 0;
}
