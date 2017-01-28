/*************************************************************************
    > File Name: StormDB_Task.cpp
    > Author:yanglongfei 
    > Mail:yanglongfei@xiyoulinux.org 
    > Created Time: 2017年01月26日 星期四 13时55分59秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Task.h"
#include "./StormDB_Utils.hpp"
#include <stdio.h>
void
Task::do_task(Task &task){
    char buf[1024];
    int t=  (task.conn)->inputBuffer_.readableSize();
    ((task.conn)->inputBuffer_).getData(buf,task.length);
    std::vector<std::string> items;
    split(buf,"\r\n",items);
    std::cout << "items.size():"<<items.size()<<std::endl;
    for(auto &i:items){
        std::cout << i << " ";
    }
    std::string Str("");
    std::cout <<std::endl;
    char *a = (task.server)->handle(items);
    std::cout <<"strlen : "<< strlen(a) <<std::endl;
    Str += items[0];
    Str += "\r\n";
    Str += a;
   // std::cout << "Str.size : "<<Str.size() <<std::endl;
    std::string str = ((task.conn)->outputBuffer_).intToByte(Str);
    ((task.conn)->outputBuffer_).append(str);
    std::cout <<"fd: "<< (task.conn)->fd_ <<std::endl;
    (task.conn)->send((task.conn)->fd_);
    //std::cout << "str.size: "<<str.size() <<std::endl;
   // std::cout << " dddd --->:" <<str <<std::endl;
}
