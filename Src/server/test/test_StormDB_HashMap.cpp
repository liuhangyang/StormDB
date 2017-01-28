/*************************************************************************
	> File Name: test_StormDB_HashMap.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 09时56分11秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Hash_DictEntry.h"
#include "../StormDB_Hash_Map.h"
#include "../StormDB_String.h"
#include "../StormDB_Hash_DictHtEntry.h"
using namespace std;
void fun(void){
    Hashmap<String> a;
    HashEntry<String> b("123","234");
    HashEntry<String> c("234","456");
    HashEntry<String> d("345","456");
    HashEntry<String> e("456","456");
    HashEntry<String> f("567","456");
    HashEntry<String> g("123","def");

    a.HashMapAdd(b);
    a.HashMapAdd(c);
    a.HashMapAdd(d);

    a.HashMapShow();
   
    a.HashMapAdd(e);
    a.HashMapAdd(f);
    
    a.HashMapShow();
    
    a.HashMapAdd(g);
    a.HashMapShow();
    String str("123");
cout << "------------------------------------------uuu--"<<endl;
    HashEntry<String> t1("qwe","def");
    HashEntry<String> t2("wer","def");
    HashEntry<String> t3("ert","def");
    HashEntry<String> t4("rre","def");
    HashEntry<String> t5("qrrwe","def");
    HashEntry<String> t6("qdwe","def");
    HashEntry<String> t7("qwfe","def");
    HashEntry<String> t8("qweg","def");
    HashEntry<String> t9("qwev","def");
    HashEntry<String> t10("qwex","def");
    HashEntry<String> t11("qwes","def");
    HashEntry<String> t12("qwse","def");
    HashEntry<String> t13("qwxe","def");
    HashEntry<String> t14("wdse","def");
    HashEntry<String> t15("wfse","def");
    HashEntry<String> t16("wsge","def");
    HashEntry<String> t17("wgse","def");

    a.HashMapAdd(t1);
    a.HashMapAdd(t2);
    a.HashMapAdd(t3);
    a.HashMapAdd(t4);
    a.HashMapAdd(t5);
    a.HashMapAdd(t6);
    a.HashMapAdd(t7);
    a.HashMapAdd(t8);
    a.HashMapAdd(t9);
    a.HashMapAdd(t10);
    a.HashMapAdd(t11);
    cout << "++++++++++++++++++++++++++++++++"<<endl;
    a.HashMapShow();
    cout <<"---------------------------------"<<endl;
    a.HashMapAdd(t12);
    cout << "######################"<<std::endl;
    a.HashMapShow();
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%"<<std::endl;
    a.HashMapAdd(t13);
    a.HashMapShow();
    a.HashMapAdd(t14);
    a.HashMapShow();
    a.HashMapAdd(t15);
    a.HashMapShow();
    a.HashMapAdd(t16);
    a.HashMapShow();
    a.HashMapAdd(t17);
a.HashMapShow();
    a.HashMapDel(t1);
    a.HashMapDel(t2);
    a.HashMapDel(t3);
    a.HashMapDel(t4);
    a.HashMapDel(t5);
    a.HashMapDel(t6);
    a.HashMapDel(t7);
    a.HashMapDel(t8);
    a.HashMapDel(t9);
    a.HashMapDel(t10);
    a.HashMapDel(t11);
    
    a.HashMapDel(t12);
    a.HashMapShow();

    a.HashMapDel(b);
    a.HashMapShow();
    a.HashMapDel(c);
    a.HashMapShow();
    a.HashMapDel(e);
    a.HashMapShow();
    a.HashMapDel(f);
    a.HashMapShow();

    std::cout << "xy" << std::endl;
    a.HashMapDel(g);
    a.HashMapShow();

}
int main(int argc,char *argv[])
{
    fun();
   return 0;
}
