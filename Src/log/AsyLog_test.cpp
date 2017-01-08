/*************************************************************************
	> File Name: AsyLog_test.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月05日 星期四 11时41分49秒
 ************************************************************************/

#include<iostream>
#include "AsyLog.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <thread>
eylib::AsyLog log(1024*1024*1024);
void func(void){
    char s[100] = "hello\n";
    log.setLevel(eylib::LogLevel::ALL);
    while(true){
       log.append(s,eylib::LogLevel::INFO);
    }
}
int main(int argc,char *argv[])
{
    std::thread t1(func);
    std::thread t2(func);
    std::thread t3(func);
    std::thread t4(func);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
   return 0;
}
