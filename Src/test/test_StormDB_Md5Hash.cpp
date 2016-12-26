/*************************************************************************
	> File Name: test_StormDB_Md5Hash.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 20时50分58秒
 ************************************************************************/

#include<iostream>
#include "../distributed_server/StormDB_Md5_Hash.h"
int main(int argc,char *argv[])
{
    CMD5HashFunc Hmd5;
    long value = Hmd5.getHashVal("yanglongfei",1);
    std::cout << "Hash(\"MD5(yanglongfei)\")"<<value<<std::endl;
   return 0;
}
