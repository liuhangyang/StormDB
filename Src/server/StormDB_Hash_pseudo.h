/*************************************************************************
	> File Name: StormDB_Hash_DictHtEntry.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月16日 星期一 10时54分58秒
 ************************************************************************/

#ifndef _STORMDB_HASH_DICTHTENTRY_H
#define _STORMDB_HASH_DICTHTENTRY_H
#include <iostream>
#include <string>
#include <vector>
#include "./StormDB_String.h"
#include "./StormDB_Hash_Entry.h"
template <typename T>
class HashDictHt{
private:
    std::vector<HashEntry<T>> data; //保存键值对的容器.
public:
    HashDictHt()= default;
    ~HashDictHt() = default;
    void HashDictHtSet(const String &a,const T& b); //向容器中添加键值对
    void HashDictHtSet(HashEntry<T> rhs); //向容器中添加键值对
    void HashDictHtDel(const String& rhs); //删除指定键的键值对
    void HashDictHtChange(const String& a,const T& b); //将键为a的键值对的值修改为b
    //将与rhs键值对中键相等的键值替换为rhs.
    void HashDictHtChange(HashEntry<T> rhs);
    bool HashDictHtTest(const String& rhs); //测试容器中是否存在键为rhs的键值对
    T HashDictHtFind(const String& rhs); //返回容器中键为rhs的值
    void HashDictHtShow();//测试函数,打印容器中所有的信息. 
    int HashDictHtSize();//返回容器中保存键值对的数目
    void HashDictHtDestory(); //销毁容器
    std::vector<HashEntry<T>> HashDictHtData(); //返回保存键值对的容器.
};
template <typename T>
void HashDictHt<T>::HashDictHtSet(const String &a,const T& b){
    HashEntry<T> key_value(a,b);
    if(HashDictHtTest(a) == true){
        HashDictHtChange(a,b);
    }else{
        data.push_back(key_value);
    }
}
template <typename T>
void HashDictHt<T>::HashDictHtSet(HashEntry<T> rhs){
    if(HashDictHtTest(rhs.HashKey()) == true){
        HashDictHtChange(rhs);
    }else{
        data.push_back(rhs);
    }
}
template <typename T>
void HashDictHt<T>::HashDictHtDel(const String& rhs){
    for(auto item = data.begin();item != data.end();++item){
        if(rhs == (*item).HashKey()){
            data.erase(item);
            break;
        }
    }
}
template <typename T>
void HashDictHt<T>::HashDictHtChange(const String &a,const T& b){
    HashDictHtDel(a);
    HashDictHtSet(a,b);
}
template <typename T>
void HashDictHt<T>::HashDictHtChange(HashEntry<T> rhs){
    HashDictHtDel(rhs.HashKey());
    HashDictHtSet(rhs.HashKey(),rhs.HashValue());
}
template <typename T>
bool HashDictHt<T>::HashDictHtTest(const String& rhs){
    for(auto item : data){
        if(rhs == item.HashKey()){
            return true;
        }
    }
    return false;
}
//在调用HashDictHtFind之前必须对调用HashDictHtTest测试这个key是否在data中
template <typename T>
T HashDictHt<T>::HashDictHtFind(const String& rhs){
    for(auto item : data){
        if(item.HashKey() == rhs){
            return item.HashValue();
        }
    }
    return NULL;
}
template <typename T>
void HashDictHt<T>::HashDictHtShow(){
    for(auto item : data){
        item.PrintHash();
    }
}
template <typename T>
int HashDictHt<T>::HashDictHtSize(){
    return data.size();
}
template <typename T>
void HashDictHt<T>::HashDictHtDestory(){
    data.erase(data.begin(),data.end());
}
template <typename T>
std::vector<HashEntry<T>> HashDictHt<T>::HashDictHtData(){
    return data;
}
#endif
