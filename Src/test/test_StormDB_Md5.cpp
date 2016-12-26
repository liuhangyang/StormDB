/*************************************************************************
	> File Name: test_StormDB_Md5.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 19时30分23秒
 ************************************************************************/

#include"../distributed_server/StormDB_Md5.h"
#include<iostream>
std::string getMd5value(const std::string str){
    MD5 md5 = MD5(str);
    return md5.hexdigest();
}
int main(int argc,char *argv[])
{
    std::cout << "Md5(\"\")="<<md5("")<<std::endl;
    std::cout << "Md5(\"admin\")="<<md5("admin")<<std::endl;
    std::cout << "Md5(\"123456789\")="<< md5("123456789")<<std::endl;
   return 0;
}
