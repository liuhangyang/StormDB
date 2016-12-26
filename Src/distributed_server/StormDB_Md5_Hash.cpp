/*************************************************************************
	> File Name: StormDB_Md5_Hash.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 19时15分25秒
 ************************************************************************/

#include<iostream>
#include "StormDB_Md5_Hash.h"
#include "StormDB_Md5.h"
#include<string.h>
long 
CMD5HashFunc::getHashVal(const char *str,int nTime){
    
    const std::string str1(str);
    MD5 md5(str1);
    char Hstr[33];
    const std::string str2 = md5.hexdigest();
    strcpy(Hstr,str2.c_str());
      long rv = ((long) (Hstr[3+nTime*4] & 0xff) << 24)
            | ((long) (Hstr[2+nTime*4] & 0xff) << 16)
            | ((long) (Hstr[1+nTime*4] & 0xff) << 8)
            | (Hstr[0+nTime] & 0xff);
    return rv & 0xffffffffL;
}
/*int main()
{
    CMD5HashFunc Hmd5;
    long value = Hmd5.getHashVal("i",1);
    std::cout << "Hash:"<<value<<std::endl;  
}*/
