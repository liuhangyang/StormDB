/*************************************************************************
	> File Name: test_StormDB_intset.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 23时07分37秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_intset.h"
using namespace std;
int main(int argc,char *argv[])
{
    Intset s;
    for(int i = 0;i < 100;++i){
        s.Insert(i);
    }
    s.print_int();
    long t = 23;
    s.Insert(t);
   s.print_int();
    cout << "find 4:"<<s.findIntset(333)<<std::endl;
    cout << "Size: "<<s.getSize()<< "BitSize: "<<s.getBitSize() <<std::endl;
    return 0;
}
