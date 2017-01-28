/*************************************************************************
	> File Name: find_last_not_of.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 13时39分34秒
 ************************************************************************/

#include<iostream>
#include <string>
#include <cstddef>
using namespace std;
int main(int argc,char *argv[])
{
    std::string str("please,erase trailing white-sapce \n");
    std::string whitespaces("\t\f\v\n\r");
    std::size_t found = str.find_last_not_of(whitespaces);
    if(found != std::string::npos){
        str.erase(found+1);
    }else{
        str.clear();
    }
    std::cout <<str <<std::endl; 
   return 0;
}
