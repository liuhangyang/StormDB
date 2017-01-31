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
    /*std::string s1("hello,world");
    std::string s2(2000,'a');
    std::string s3(1000,'a');

    eylib::Buffer buffer;
    buffer.append(s1);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s2);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    buffer.append(s3);
    printf("readable = %d\nwriteable = %d\n",buffer.readableSize(),buffer.writeableSize());
    */
    int t = 5;
    std::string str("aaaaa");
    eylib::Buffer buffer;
    buffer.appendInt32(t);
    buffer.append(str);
    t = buffer.peekInt32();
    buffer.moveReadIndex(sizeof(int32_t));
    printf("t=%d\n",t);
    char buffer1[6];
    buffer.getposLength(5,buffer1);
    printf("buffer:%s\n",buffer1);
   return 0;
}
