/*************************************************************************
	> File Name: AsyLog.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 22时20分18秒
 ************************************************************************/

#include "AsyLog.h"
#include "LogFile.h"
#include "timestamp.h"
#include <stdio.h>
#include <string.h>
#include <memory>
#include "fixBuffer.h"
#include <mutex> 
#include <condition_variable>
#include <functional>
#include <pthread.h>
using  namespace eylib;
AsyLog::AsyLog(int rollSize)
    :rollSize_(rollSize),
    running_(true),
    currentBuffer_(new FixBuffer()),
    nextBuffer_(new FixBuffer()),
    acceptThread_(std::bind(&AsyLog::threadFunc,this)){}
AsyLog::~AsyLog(){
    stop();
}
void
AsyLog::setLevel(LogLevel level){
    currentLevel_ = level;
}
bool
AsyLog::aboveLevel(LogLevel level){
    return level <= currentLevel_;
}
void
AsyLog::append(char *logline,LogLevel level){
    if(aboveLevel(level)){
        std::lock_guard<std::mutex> guard(mutex_);
        //与时间以及线程id等字符串连接.
        std::string log1(logline); //日志内容
        std::string log2(timestamp_.toStringTime()); //获得时间戳的字符串
        char log3[30];
        snprintf(log3,sizeof(log3),"threadid[%ld]: ",pthread_self()); //获得线程id的字符
        std::string log4(toStringForLevel(level)); //获得等级对应的字符串
        log2 = log2 + log3 + log4 + log1;
        writeBuffer(log2.c_str(),log2.size()); //写入buffer;
    }
}
void
AsyLog::writeBuffer(const char *logline,int len){
    if(currentBuffer_->writeableSize() >= len){
        currentBuffer_->append(logline,len);
    }else{
        buffers_.push_back(std::move(currentBuffer_)); //返回指针,自己变为空.
        if(nextBuffer_){
           // printf("将nextBuffer_的控制权交给currentBuffer_\n");
            currentBuffer_ = std::move(nextBuffer_); //将nextBuffer_的控制权交给currentBuffer
        }else{
           // printf("给currentBuffer_重新申请buffer\n");
            currentBuffer_.reset(new FixBuffer); //申请一块新的buffer
        }
        currentBuffer_->append(logline,len);
        condition_.notify_one(); //唤醒后台线程.
    }
}
std::string
AsyLog::toStringForLevel(LogLevel level){
    switch(level){
        case LogLevel::OFF:
            return std::string("OFF ");
            break;
        case LogLevel::FATVAL:
            return std::string("FATAL ");
            break;
        case LogLevel::ERROR:
            return std::string("ERROR ");
            break;
        case LogLevel::WARN:
            return std::string("WARN ");
            break;
        case LogLevel::INFO:
            return std::string("INFO ");
            break;
        case LogLevel::DEBUG:
            return std::string("DEBUG ");
            break;
        case LogLevel::ALL:
            return std::string("ALL ");
            break;
        default:
            return std::string("UNKNOWN ");
    }
    return NULL;
}
void
AsyLog::stop(void){
    if(running_){
        running_ = false;
        acceptThread_.join(); //等待后台线程退出
        printf("日志系统已关闭\n");
    }
}
void
AsyLog::threadFunc(void){
    std::unique_ptr<FixBuffer> newBuffer1(new FixBuffer);
    std::unique_ptr<FixBuffer> newBuffer2(new FixBuffer);
    std::vector<std::unique_ptr<FixBuffer>> buffersToWrite;
    //printf("rollSize_:%d\n",rollSize_);
    LogFile output(rollSize_);
    buffersToWrite.reserve(16);
    while(running_){
        {
            std::lock_guard<std::mutex> guard(mutex_); //临界区加锁. 
            if(buffers_.empty()){
                //printf("buffer是空的,刷盘线程等待三秒\n");
                condition_.wait_for(mutex_,std::chrono::seconds(3));
            }
            buffers_.push_back(std::move(currentBuffer_));
            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_); //交换俩个容器. 
            if(!nextBuffer_){
                //printf("nextBuffer_为空,给nextBuffer_重新赋值\n");
                nextBuffer_ = std::move(newBuffer2);
            }
        }
        assert(!buffersToWrite.empty());
        if(buffersToWrite.size() > 25){
            //日志异常
           // printf("buffersToWrite.size()大于25\n");
        }
        //将buffer中的内容写进文件中
        for(int i = 0;i < buffersToWrite.size();i++){
            output.append(buffersToWrite[i]->getReadPeek(),buffersToWrite[i]->readableSize());
        }
        if(buffersToWrite.size() > 2){
            buffersToWrite.resize(2);
        }
        //把最初的currentBuffer_的控制权给neeBuffer1;就相当于是环形利用4个buffer;
        if(!newBuffer1){

            assert(!buffersToWrite.empty());
            newBuffer1 = std::move(buffersToWrite[0]);
            newBuffer1 -> resetBuffer(); //重置buffer;
        }
        //也就是相当于把nextBuffer_控制权交给buffersToWrite[0];
        if(!newBuffer2){
            assert(!buffersToWrite.empty());
            newBuffer2 = std::move(buffersToWrite[1]);
            newBuffer2 -> resetBuffer();
        }
        buffersToWrite.clear();
    }
}
