/*************************************************************************
	> File Name: test_StormDB_String.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 11时37分05秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_String.h"
using namespace std;
int main(int argc,char *argv[])
{
    String a("ssssssssss");
    String b;
    char c[10] = "doubiias";

    cout << a << " Size:" <<a.getSize() << "free: "<<a.getFree() << endl;
    cin >> b;
    
    cout << b << " Size:" <<b.getSize() << "free: "<<b.getFree() << endl;
    b=a;
    cout << b << " Size:" <<b.getSize() << "free: "<<b.getFree() << endl;
    b[0] = '1'; 
    cout << b << " Size:" <<b.getSize() << "free: "<<b.getFree() << endl;
    a+=b;

    cout << a << " Size:" <<a.getSize() << "free: "<<a.getFree() << endl;
   cout <<(a>b) << " "<<(a <b )<<" "<<(a==b) <<endl;
    a += c;

    cout << a << " Size:" <<a.getSize() << "free: "<<a.getFree() << endl;
    cout << b << " Size:" <<b.getSize() << "free: "<<b.getFree() << endl;
    String d =a+b;

    cout << d << " Size:" <<d.getSize() << "free: "<<d.getFree() << endl;

    d =a +c;
    
    cout << d << " Size:" <<d.getSize() << "free: "<<d.getFree() << endl;
    b.StringSizeClear(1,2);

    cout << b << " Size:" <<b.getSize() << "free: "<<b.getFree() << endl;
    d.StringClear();

    cout << d << " Size:" <<d.getSize() << "free: "<<d.getFree() << endl;
    cout << "-----------------------------------------------------"<<endl;
    Hashmap<String> map(hash);
    map.HashMapShow();
    return 0;
}
