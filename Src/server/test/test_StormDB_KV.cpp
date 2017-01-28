/*************************************************************************
	> File Name: test_StormDB_KV.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月18日 星期三 09时59分37秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_Hash_Entry.h"
#include "../StormDB_KV.h"
#include <unistd.h>
#include <string>
using namespace std;
void func(){
    KeyVal k("123",0,1);
    void *obj;
    HashEntry<std::string> a("ynag","14");
    HashEntry<std::string> a1("lomg","23");
    HashEntry<std::string> a2("fei","45");
    HashEntry<std::string> a3("wr3","34");
    obj = new HashEntry<string>;
    (*(HashEntry<std::string>*)obj) = a3;
    if(k.KeyValDel(obj) == false){
        cout << "error" << endl;
    }
    (*(HashEntry<std::string> *)obj) = a;
    k.KeyValAdd(obj);
   // (*(HashEntry<std::string> *)obj) = a3;
    if(k.KeyValDel(obj) == false){
        cout << "error" <<endl;
    }

    (*(HashEntry<std::string> *)obj) =a1;
    k.KeyValAdd(obj);

    (*(HashEntry<std::string> *)obj) = a2;
    k.KeyValAdd(obj);
    
    delete (HashEntry<std::string> *)obj;
    void *buff;
    buff = new vector<HashEntry<std::string>>;
    k.KeyValue(buff);
    for(auto item : (*(vector<HashEntry<std::string>> *)buff)){
        item.PrintHash();
    }
    cout <<"size: "<< k.KeyValSize() <<endl;
    //k.KeyValDestory();
    cout << "size: "<<k.KeyValSize()<<endl; 
    //delete (HashEntry<std::string> *)obj;
    //delete (vector<HashEntry<std::string>> *)buff;
    cout << "type: "<<k.GetType() << endl;
    cout << "hash: "<<k.GetHash() << endl;
    cout << "key: "<<k.GetKey() <<endl;
}
void func1(){
    KeyVal k("123",2,0);
    std::string a("1");
    std::string a1("2");
    std::string a2("3");
    std::string a3("4");
    std::string a4("5");
   // std::string a5("");
    
    void *obj;
    void *buff;

    obj = new string;
    (*(string *)obj) = a;
    k.KeyValAdd(obj);
    (*(string *)obj) = a1;
    k.KeyValAdd(obj);
    (*(string *)obj) = a2;
    k.KeyValAdd(obj);
    (*(string *)obj) = a3;
    k.KeyValAdd(obj);
    (*(string *)obj) = a4;
    k.KeyValAdd(obj);
    //(*(string *)obj) = a5;
   // k.KeyValAdd(obj);
    
    k.KeyValDel(obj);
    

    cout <<"size: "<<k.KeyValSize() <<endl;
    buff = new vector<string>;
    k.KeyValue(buff);
    for(auto item : (*(vector<string> *)buff)){
        cout << item << endl;
    }
    delete (vector<string> *)buff;
    buff = new vector<string>;
    for(auto item : (*(vector<string> *)buff)){
        cout << item << endl;
    }
    delete (vector<string> *)buff;
    k.KeyValDestory();
    //cout << k.KeyValSize() <<endl;

}
void func2(){
    String a("123");
    void *obj;
    obj = new String;
    (*(String *)obj) = a;
    KeyVal k("123",3,0);
    k.KeyValAdd(obj);
    delete (String *)obj;
    void *buff;
    buff = new String;
    k.KeyValue(buff);
    cout << (*(String *)buff) <<endl;
    delete (String *)buff;
}
void func3(){
    KeyVal k("123",4,0);
    std::string a("1");
    std::string a1("2");
    std::string a2("3");
    std::string a3("4");
    std::string a4("5");

    void *obj;
    obj = new string; 
    (*(string *)obj) = a;
    k.KeyValAdd(obj);
    (*(string *)obj) = a1;
    k.KeyValAdd(obj);
    (*(string *)obj) = a2;
    k.KeyValAdd(obj);
    (*(string *)obj) = a3;
    k.KeyValAdd(obj);
    (*(string *)obj) = a4;
    k.KeyValAdd(obj);
    
    void *buff;
    buff = new string;
    k.KeyValue(buff);
    cout << "size :" <<k.KeyValSize() <<endl;
    cout << (*(string *)buff) << endl;
    k.KeyValDel(obj);
    k.KeyValue(buff);
    cout << (*(string *)buff)<<endl;

    cout << "size: "<<k.KeyValSize() <<endl;
    k.KeyValDestory();
    cout << "size: "<<k.KeyValSize()<<endl;
    delete (string *)obj;
    delete (string *)buff;
}
void func4(){
    KeyVal k("123",5,0);
    std::string a("1");
    std::string a1("2");
    std::string a2("3");
    std::string a3("4");
    std::string a4("5");
    void *obj;
    obj = new string;
    (*(string *)obj) = a;
    k.KeyValAdd(obj);
    (*(string *)obj) = a1;
    k.KeyValAdd(obj);
    (*(string *)obj) = a2;
    k.KeyValAdd(obj);
    (*(string *)obj) = a3;
    k.KeyValAdd(obj);
    (*(string *)obj) = a4;
    k.KeyValAdd(obj);

    void *buff;
    buff = new string;
    k.KeyValue(buff);
    cout << (*(string *)buff)<<endl;
    k.KeyValDel(obj);
    k.KeyValue(buff);
    cout << (*(string *)buff)<<endl;
    cout << "size: "<< k.KeyValSize() <<endl;
    k.KeyValDestory();
    cout <<"size: "<< k.KeyValSize()<<endl;
    delete (string *)obj;
    delete (string *)buff;

    
}
int main(int argc,char *argv[])
{
    func4();
   return 0;
}
