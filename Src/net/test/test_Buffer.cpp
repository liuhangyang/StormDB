/*************************************************************************
	> File Name: test_Buffer.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 22时01分11秒
 ************************************************************************/

#include "../Buffer.h"
#include <string>
#include<stdio.h>
int main(int argc,char *argv[])
{
    std::string s1("hello,world");
    std::string s2(2000,'a');
    std::string s3(1000,'a');

    eylib::Buffer buffer;
    buffer.append(s1);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s2);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s3);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());

   return 0;
}
