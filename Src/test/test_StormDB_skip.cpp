/*************************************************************************
	> File Name: StormDB_test_skip.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月22日 星期四 08时25分12秒
 ************************************************************************/
#include"../server/StormDB_skiplist.h"
#include<iostream>
int main(int argc,char *argv[])
{
    list_skip<long> temp(10000);
    for(long i = 0; i < 30;i++){
        temp.Insert(i);
    }
    temp.print();
    temp.Delete(5);
    temp.Delete(4);
    temp.print();
    long p = temp.Search(6);
    std::cout << p<<std::endl;
    long q = temp.Search(5);
    std::cout << q<<std::endl;
   return 0;
}
