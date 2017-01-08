/*************************************************************************
	> File Name: test_timestamp.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 17时06分50秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string.h>
#include  "../timestamp.h"
#include <time.h>
#include <sys/time.h>
int main(int argc,char *argv[])
{
    struct tm time = eylib::Timestamp().now();
    eylib::Timestamp t;
    char *p = t.toStringTime();
    printf("%s\n%d\n",p,strlen(p));
   return 0;
}
