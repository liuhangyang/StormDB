/*************************************************************************
	> File Name: test_Endian.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月22日 星期日 17时29分00秒
 ************************************************************************/

#include<iostream>
#include "../Endian.h"
using namespace std;
int main(int argc,char *argv[])
{
    int64_t  t = 45;
    int64_t r = hostToNetwork64(t);
    printf("r:%ld\n",r);
    int64_t d = networkToHost64(r);
    printf("d:%ld\n",d);
   return 0;
}
