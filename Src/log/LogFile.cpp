/*************************************************************************
	> File Name: LogFile.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 18时19分48秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "LogFile.h"
using namespace eylib;
LogFile::LogFile(int rollSize):rollSize_(rollSize),fillSize_(0),fileNumbers_(1){
    fd_ = open("/home/yang/log/mylog.log",O_WRONLY | O_APPEND | O_CREAT,S_IWUSR | S_IRUSR | S_IXUSR);
    assert(fd_> 0);
}
LogFile::~LogFile(){
    close(fd_);
}
void
LogFile::append(char *log,int len){
    int ret = write(fd_,log,len);
    rollFile(ret);
    assert(ret == len);
}
void 
LogFile::rollFile(int curLen){
    fillSize_ += curLen;
    //printf("fillSize_:%d,rollSize_:%d\n",fillSize_,rollSize_);
    if(fillSize_ >= rollSize_){
        printf("1G满了\n");
        fillSize_ = 0;
        char command[80];
        snprintf(command,sizeof(command),"mv /home/yang/log/mylog.log  /home/yang/log/mylog%d.log",fileNumbers_);
        fileNumbers_++;
        //改当前文件名为fileName;
        system(command);
        //重新创建一个mylog.log文件.
        fd_ = open("/home/yang/log/mylog.log",O_WRONLY | O_APPEND | O_CREAT,S_IWUSR | S_IRUSR | S_IXUSR);
        assert(fd_ > 0);
    }
}
