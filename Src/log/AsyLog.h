/*************************************************************************
	> File Name: asyLog.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 18时38分19秒
 ************************************************************************/

#ifndef _ASYLOG_H
#define _ASYLOG_H
#include <memory>
#include "fixBuffer.h"
#include "timestamp.h"
#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <assert.h>
#include <condition_variable>
namespace eylib{
    enum LogLevel{
        OFF, //关闭所有日志记录
        FATVAL, //导致程序退出的错误
        ERROR, //发生了错误但不影响系统的运行.
        WARN , //会出现潜在的错误情形
        INFO, //系统发生了哪些事情. 
        DEBUG, //调试程序有关的信息
        ALL, //输出所有日志. 
    };
    class AsyLog{
    public:
        AsyLog(int rollSize);
        ~AsyLog();
        void append(char* logline,LogLevel level); //添加日志行
        void setLevel(LogLevel level); //设置日志的水平
        void stop(void); 
    private:
        void threadFunc(void); //线程函数
        bool aboveLevel(LogLevel level);  //判断某条日志等级是否超过我们锁设的level;
        void writeBuffer(const char* logline,int len); //将日志写入buffer中.
        std::string toStringForLevel(LogLevel level); //将对应的level转换为字符串. 

        int rollSize_;     //文件达到多大时滚动
        bool running_; 
        std::unique_ptr<FixBuffer> currentBuffer_;  //当前的buffer
        std::unique_ptr<FixBuffer> nextBuffer_;  //备用buffer;
        std::vector<std::unique_ptr<FixBuffer>> buffers_; //保存buffer的vector;
        std::thread acceptThread_;  //后台接受数据的线程. 
        std::mutex mutex_;        //互斥变量
        std::condition_variable_any condition_;   //条件变量
        Timestamp timestamp_;     //时间戳
        LogLevel currentLevel_;    //当前日志等级
    };
}
#endif
