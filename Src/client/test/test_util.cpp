/*************************************************************************
	> File Name: test_util.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 13时56分13秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Utils.hpp"
using namespace std;
int main(int argc,char *argv[])
{
    std::string str("yang long fei");
    std::string t;
    t = rtrim(str);
    std::cout << t <<std::endl;
    std::cout << t.size() <<std::endl;
    std::vector<std::string> item;
    split(str,"' '",item);
    for(auto a:item){
        std::cout << a <<std::endl;;
    }
    return 0;
}
