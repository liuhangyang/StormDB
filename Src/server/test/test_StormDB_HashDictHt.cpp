/*************************************************************************
	> File Name: test_StormDB_HashDictHt.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月16日 星期一 11时51分46秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Hash_DictEntry.h"
#include "../StormDB_Hash_DictHtEntry.h"
#include "../StormDB_String.h"
#include "../StormDB_Hash_Map.h"
using namespace std;
int main(int argc,char *argv[])
{
    HashEntry<String> a;
    int i = 123;
    HashEntry<int> b("yang",i);
    int c;
    String d;
    String j = "long";

    a.HashSet("fei",j);
    a.PrintHash();
    b.PrintHash();
    c =b.HashValue();
    d = b.HashKey();
    std::cout << "b.key: " << d << "b.value: "<< c<<std::endl;
    c = 2;
    d = "111";
    b.PrintHash();

    HashDictHt<String> hash;
    HashEntry<String> hash1("123","456");
    String str;
    hash.HashDictHtSet(a);
    hash.HashDictHtSet(j,d);
    cout << hash.HashDictHtSize() << endl;

    if(hash.HashDictHtTest(j) == true){
        str = hash.HashDictHtFind(j);
        cout << "Jvalue: "<< str<<endl;
    }else{
        cout << "don,t find!"<<endl;
    }
    hash.HashDictHtShow();
    cout << hash.HashDictHtSize()<<endl;
    hash.HashDictHtSet("huxj","abc");
    hash.HashDictHtShow();
    cout << "-------------------------------------"<<endl;
    Hashmap<String> map(hash);
    map.HashMapShow();
   return 0;
}
