/*************************************************************************
	> File Name: test_StormDB_Ziplist.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 15时23分41秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Ziplist.h"
using namespace std;
int main(int argc,char *argv[])
{
    Ziplist<int> a;
    Ziplist<char> b;

    a.Ziplist_add(1);
    a.Ziplist_add(2);
    a.Ziplist_add(3);
    a.Ziplist_add(4);
    a.Ziplist_add(5);
    a.Ziplist_add(6);
    a.Ziplist_add(7);
    a.Ziplist_del(1);
    a.Ziplist_show();
    a.Ziplist_del_more(2,4);
    a.Ziplist_show();
    cout << "Size: " << a.Ziplist_size() << endl;
    cout << "size_bytes: " << a.Ziplist_size_bytes() << endl;
    b.Ziplist_add('1');
    cout << "Size: " << b.Ziplist_size() << endl;
    cout << "size_bytes: " << b.Ziplist_size_bytes() << endl;
    if(b.Ziplist_find('b')){
        cout << " oh,my God!" <<endl;
    }
    vector<int> c;
    c = a.Ziplist_return();
    cout << c[0] <<endl;
    cout << c[1] <<endl;
    cout << c[2] << endl;
    a.Ziplist_destory();
    cout << "Size: " << a.Ziplist_size() << endl;
    cout << "size_bytes: " << a.Ziplist_size_bytes() << endl;
    

   return 0;
}
