/*************************************************************************
	> File Name: test_Command.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 20时38分08秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Command.hpp"
using namespace std;
int main(int argc,char *argv[])
{
    Command t("set");
    std::cout << t.getbuffer()<<std::endl;


   return 0;
}
