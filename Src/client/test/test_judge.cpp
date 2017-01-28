/*************************************************************************
	> File Name: test_judge.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月22日 星期日 12时02分12秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Judge.h"
using namespace std;
int main(int argc,char *argv[])
{
    Judge judge;
    const char* result;
    result = judge.JudgeCommand("SET",2);
    std::cout << result <<std::endl;
    return 0;
}

