/*************************************************************************
	> File Name: test_upper_bound1.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月29日 星期四 10时01分01秒
 ************************************************************************/

#include<iostream>
#include<map>
int main(int argc,char *argv[])
{
    std::map<long,std::string> v;
    v[234] = "ddd";
    v[567] = "rrr";
    v[789] = "dvfvf";
    v[899] = "dddd";
    auto one = v.upper_bound(444444);
    std::cout <<"one.first:"<<one ->first<<std::endl;
   return 0;
}
