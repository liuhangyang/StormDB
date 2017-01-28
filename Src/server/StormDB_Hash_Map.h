/*************************************************************************
	> File Name: StormDB_Hash_Map.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月16日 星期一 12时45分55秒
 ************************************************************************/

#ifndef _STORMDB_HASH_MAP_H
#define _STORMDB_HASH_MAP_H
#include <iostream>
#include <list>
#include <vector>
#include "./StormDB_Hash_Entry.h"
#include "./StormDB_String.h"
#include "./StormDB_Hash_pseudo.h"
//返回HashEntry中键值对中键的char* 类型。
#define GET_CHAR(data) data.HashKey().StringGetChar() 

#define HASH_DEFAULT 128 //由伪哈希向哈希转换时哈希表的大小
#define REHASH_DEFAULT 10  //每次渐近式哈希,由hash向rehash转换的个数.
#define HASH_MIN 4 //创建空哈希表时哈希表的大小.

template <typename T>
class Hashmap{
private:
    unsigned long used; //键值对保存在hash表中的大小
    unsigned long size; //hash表的大小
    std::vector<std::list<HashEntry<T>>> hash; //hash表的实现
    unsigned long reused; //键值对保存在rehash表中的大小
    unsigned long resize; //rehash表的大小
    std::vector<std::list<HashEntry<T>>> rehash; //rehash表的实现.
    int rehashhidx; //标志rehash是否使用
public:
    Hashmap(); //初始化空哈希表.
    Hashmap(HashDictHt<T> rhs); //由伪哈希向哈希表的转换(包括其内键值对的移动)
    void HashMapAdd(HashEntry<T> rhs); //向哈希表中添加键值对
    void HashMapDel(HashEntry<T> rhs);//删除哈希表中的键值对rhs

    //由hash向rehash渐近式哈希的迁移,包括当hash表迁移完所有后将用rehash代替hash，并将新的rehash置空.
    void HashMapRehash();
    void HashMapChange(HashEntry<T> rhs);//将与rhs键值对的键相等的键值对替换为rhs;
    void HashMapDestory();  //清空hash表,并再次初始化它.
    void HashMapShow(); //测试函数,打印哈希表的数据
    bool HashMapFind(HashEntry<T> rhs); //测试rhs键值对是否存在在哈希表中
    T HashMapVaue(String rhs); //返回哈希表中键为rhs的键值对的值
    std::vector<HashEntry<T>> HashMapAll(); //将所有的节点保存到vector容器中返回.
    int HashMapSize();

    unsigned int GetKey_char(const void *key); //hash函数
    unsigned int GetKey_int(unsigned int key); //hash函数
};
template <typename T>
Hashmap<T>::Hashmap(){
    //初始化一个大小HASH_MIN的hash表中的大小
    std::vector<std::list<HashEntry<T>>> vec(HASH_MIN);
    used = 0;
    size = HASH_MIN;
    //用vec来对hash进行初始化
    hash = vec;
    resize = 0;
    reused = 0;
    rehashhidx = -1;
}
template <typename T>

Hashmap<T>::Hashmap(HashDictHt<T> rhs){
    //data为包含了伪哈希的所有皮键值对的容器
    std::vector<HashEntry<T>> data = rhs.HashDictHtData();
    //初始化一个大小为HASH_DEFAULT的表
    std::vector<std::list<HashEntry<T>> > vec(HASH_DEFAULT);
    
    used = 0;
    size = HASH_DEFAULT;
    hash = vec;

    reused = 0;
    resize = 0;
    rehashhidx = -1;
    //将伪哈希中的键值对添加到hash表中的大小
    for(auto item : data){
        HashMapAdd(item);
    }
}
template <typename T>
void Hashmap<T>::HashMapRehash(){
    int i = 0;
    int sum = 0;
    //实现了键值对从hash向rehash迁移.
    if(resize == 0){
        return;
    }
    while(1){
        while(hash[i].size() != 0){
            auto item = hash[i].begin();
            rehash[(*item).GetHashNum() % resize].push_front(*item);
            hash[i].erase(item);
            reused++;
            rehashhidx++;
            used--;
            ++sum;
        }
        if((sum > REHASH_DEFAULT) || (used == 0)){
            break;
        }
        ++i;
    }
    //若迁移完成,则用rehash代替hash，并创建新的rehash
    if(used == 0){
        rehashhidx = -1;
        hash = rehash;
        used = reused;
        size = resize;
        reused = 0;
        resize = 0;
        std::vector<std::list<HashEntry<T>>>().swap(rehash);
    }
}
template <typename T>
void Hashmap<T>::HashMapAdd(HashEntry<T> rhs){
    if(HashMapFind(rhs) == true){
        HashMapChange(rhs);
        return;
    }
    unsigned int key = GetKey_char(GET_CHAR(rhs));
    rhs.SetHashKey(key);

    //当hash表的用量大于hash表大小的时候,启用rehash
    if((rehashhidx == -1) && (used/size >= 1)){
        rehashhidx = 0;
        resize = size * 2;
        reused = 0;
        std::vector<std::list<HashEntry<T>>> vec_rehash(resize);
        rehash = vec_rehash;
    }
    //标志不为-1,代表rehash正在使用,将数据添加到rehash表中,并进行数据迁移
    if(rehashhidx != -1){
        if(resize == 0){
            return;
        }
        rehash[key%resize].push_front(rhs);
        reused++;
        HashMapRehash();
    }else{
        hash[key%size].push_front(rhs);
        used++;
    }
}
template <typename T>
void Hashmap<T>::HashMapDestory(){
    //用swap的方法对vector容器进行销毁工作
    std::vector<std::list<HashEntry<T>>>().swap(hash);
    std::vector<std::list<HashEntry<T>>>().swap(rehash);

    //重新对hash表进行初始化
    std::vector<std::list<HashEntry<T>>> vec(HASH_MIN);
    used = 0;
    size = HASH_MIN;
    hash = vec;
    resize = 0;
    rehashhidx = -1;
}
//每次HashMapFind函数需要该函数返回true位前置条件
template <typename T>
bool Hashmap<T>::HashMapFind(HashEntry<T> rhs){
    unsigned int key = GetKey_char(GET_CHAR(rhs));
    for(auto item : hash[key % size]){
        if(rhs.HashKey() == item.HashKey()){
            return true;
        }
    }
    if(rehashhidx != -1){
        for(auto item : rehash[key % resize]){
            if(rhs.HashKey() == item.HashKey()){
                return true;
            }
        }
    }
    return false;
}
template <typename T>
void Hashmap<T>::HashMapDel(HashEntry<T> rhs){
    if(HashMapFind(rhs) == false){
        return;
    }
    unsigned int hash_key = GetKey_char(GET_CHAR(rhs));
    //若hash表大小是使用量的十倍则用rehash表进行对hash表减少空间的操作.
    if((used !=0 )&&(size/used >= 10)&& (rehashhidx == -1)){
        rehashhidx = 0;
        resize = size / 2;
        reused = 0;
        std::vector<std::list<HashEntry<T>>> vec_rehash(resize);
        rehash = vec_rehash;
    }
    //在rehash表中进行delete操作
    if(rehashhidx != -1){
        auto item = rehash[hash_key % resize].begin();
        while(item != rehash[hash_key % resize].end()){
            if(rhs.HashKey() == (*item).HashKey()){
                rehash[hash_key % resize].erase(item);
                reused--;
                HashMapRehash();
                return;
            }else{
                item++;
            }
        }
        HashMapRehash();
    }
    //在hash表中进行delete操作
    auto item = hash[hash_key % size].begin();
    while(item != hash[hash_key % size].end()){
        if(rhs.HashKey() == (*item).HashKey()){
            hash[hash_key % size].erase(item);
            used--;
            return;
        }else{
            item++;
        }
    }
}
template <typename T>
void Hashmap<T>::HashMapChange(HashEntry<T> rhs){
    HashMapDel(rhs);
    HashMapAdd(rhs);
}
template <typename T>
T Hashmap<T>::HashMapVaue(String rhs){
    unsigned int key = GetKey_char(rhs.StringGetChar());
    for(auto item : hash[key % size]){
        if(rhs == item.HashKey()){
            return item.HashValue();
        }
    }
    if(rehashhidx != -1){
        for(auto item : rehash[key % resize]){
            if(rhs == item.HashKey()){
                return item.HashValue();
            }
        }
    }
}
template <typename T>
std::vector<HashEntry<T>> Hashmap<T>::HashMapAll(){
    std::vector<HashEntry<T>> vec;
    for(auto item : hash){
        for(auto itter : item){
            vec.push_back(itter);
        }
    }
    if(rehashhidx != -1){
        for(auto item : rehash){
            for(auto iterr : item){
                vec.push_back(iterr);
            }
        }
    }
    return vec;
}
template <typename T>
int Hashmap<T>::HashMapSize(){
    return used + reused;
}
template <typename T>
void Hashmap<T>::HashMapShow(){
    std::cout << "hash: " <<std::endl;
    std::cout << "size: " <<size << " used: " <<used << " hash_size: "<<hash.size() << std::endl;
    int i = 0;
    for(auto item : hash){
        for(auto it : item){
            std::cout <<"i: " << i <<std::endl;
            std::cout << it.HashKey() << "------"<<it.HashValue()<<"------"<<it.GetHashNum()<<std::endl;

        }
        i++;
    }
    std::cout << "rehash: " <<std::endl;
    std::cout << "resize: "<<resize << "reused: "<<reused << " rehash_size: "<< rehash.size() << std::endl;
    i = 0;
    for(auto item : rehash){
        for(auto it : item){
            std::cout << i <<" :" <<std::endl;
            std::cout << it.HashKey() << "-----" << it.HashValue() << "------"<<it.GetHashNum() <<std::endl;
        }
        i++;
    }
    std::cout << "rehashhidx: "<< rehashhidx <<std::endl;
    std::cout << "--------------------------------------------------------"<<std::endl;
}
template <typename T>
unsigned int Hashmap<T>::GetKey_int(unsigned int key){
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += (key << 11);
    key ^= (key >> 16);
    return key;
}
template <typename T>
unsigned int Hashmap<T>::GetKey_char(const void *key){
    uint32_t seed = 5635;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    int len = 8;
    uint32_t h = seed ^ len;
    const unsigned char* data = (const unsigned char* )key;

    while(len >= 4){
        uint32_t k = *(uint32_t *)data;

        k *= m;
        k ^= k >>r;
        k *= m;
        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }
    switch(len){
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
        h *= m;
    }
    h ^=  h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h;

}

#endif
