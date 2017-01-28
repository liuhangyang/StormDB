/*************************************************************************
	> File Name: StormDB_Hash_Entry.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月16日 星期一 09时39分58秒
 ************************************************************************/

#ifndef _STORMDB_HASH_ENTRY_H
#define _STORMDB_HASH_ENTRY_H
#include "./StormDB_String.h"
template <typename T>
class HashEntry{
private:
    String key; //键值对的键
    T value;  //键值对的值
    unsigned int hash_num; //键值对键的hash值.
public:
    HashEntry()=default;
    HashEntry(const String &Key,const T &data); //初始化该键值对
    ~HashEntry()=default;
    void HashSet(const String &Key,const T &data); //向一个键值写入信息
    void PrintHash();//打印键值对的所有信息
    void SetHashKey(unsigned int a);
    String HashKey(); //返回键值对的键
    T HashValue(); //返回键值对的值
    unsigned int GetHashNum(); //返回键值对的hash值
};
template <typename T>
HashEntry<T>::HashEntry(const String &Key,const T &data){
    key = Key;
    value = data;
    hash_num = 0;
}
template <typename T>
void HashEntry<T>::HashSet(const String &Key,const T &data){
    key = Key;
    value = data;
    hash_num = 0;
}
template <typename T>
void HashEntry<T>::SetHashKey(unsigned int a){
    hash_num = a;
}
template <typename T>
void HashEntry<T>::PrintHash(){
    std::cout << key << "------"<< value<< "--------"<< hash_num <<std::endl;
}
template <typename T>
String HashEntry<T>::HashKey(){
    return key;
}
template <typename T>
T HashEntry<T>::HashValue(){
    return value;
}
template <typename T>
unsigned int HashEntry<T>::GetHashNum(){
    return hash_num;
}
#endif
