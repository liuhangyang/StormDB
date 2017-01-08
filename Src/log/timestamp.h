/*************************************************************************
	> File Name: timestamp.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 16时39分36秒
 ************************************************************************/

#ifndef _TIMESTAMP_H
#define _TIMESTAMP_H
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
namespace eylib
{

    class Timestamp{
    public:    
        Timestamp(){

        }
        static struct tm now(void) //获取当前tm格式的时间
        {
            struct timeval tv;
            struct tm time;

            gettimeofday(&tv,NULL); //获取微妙,秒值.
            localtime_r(&tv.tv_sec,&time); //将结果填充到time指针指向的内存里面. 
            time.tm_year += 1900;
            time.tm_mon += 1;
            return time;
        }
        static timeval getTime(void){
            struct timeval tv;
            gettimeofday(&tv,NULL);
            return tv;
        }
        char *toStringTime(void) //将时间转换为字符串并返回. 
        {
            struct tm time;
            bzero(str_,sizeof(str_));
            time = now();
            snprintf(str_,sizeof(str_),"%d-%d-%d %d:%d:%d ",time.tm_year,time.tm_mon,time.tm_mday,time.tm_hour,time.tm_min,time.tm_sec);
            return str_;
        }
        static int getTimeDiff(timeval v1,timeval v2)//获得俩时间的时间差,返回值为微妙.
        {
            int t;
            t = v1.tv_sec*1000000 + v1.tv_usec - v2.tv_sec*1000000 - v2.tv_usec;
            t = abs(t);
            return t;
        }
    private: 
        char str_[200];
    };
}
#endif
