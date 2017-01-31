/*************************************************************************
	> File Name: StormDB_DB.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月18日 星期三 16时10分09秒
 ************************************************************************/

#include "./StormDB_DB.h"
using namespace std;
StormDB::StormDB(int hashsize,int rehashsize){
    std::vector<std::list<KeyVal>> vec(hashsize);

    used = 0;
    size = hashsize;
    hash = vec;
    resize = 0;
    reused = 0;
    rehashhidx = -1;
    rehash_default = rehashsize;
}
void StormDB::StormDBRehash(){
    int i = 0;
    int sum = 0;
    //实现了键值从hash向rehash的迁移
    while(1){
        while(hash[i].size() != 0){
            auto item = hash[i].begin();
            KeyVal a(*item);
            rehash[(*item).GetHash() % resize].push_front(a);
            hash[i].erase(item);
            reused++;
            rehashhidx++;
            used--;
            sum++;
        }
        if((sum > rehash_default) || (used == 0)){
            break;
        }
        i++;
    }
    //若迁移完成,则用rehash代替hash,并创建新的rehash;
    if(used == 0){
        rehashhidx = -1;
        hash = rehash;
        used = reused;
        size = resize;
        reused = 0;
        resize = 0;
        sum = 0;
        std::vector<std::list<KeyVal>>().swap(rehash);
    }
}
void
StormDB::StormDBAdd(KeyVal rhs){
    char *a = new char[rhs.GetKey().size()+10];
    StormDB_CStr(a,rhs.GetKey());
    unsigned int key = GetKey_char(a);
    rhs.SetHashKey(key);
    delete []a;

    //当hash表的用量大于hash表大小使.启用rehash
    if((rehashhidx == -1) && (used/size >= 1)){
        std::cout << "rehash开始:"<<std::endl;
        rehashhidx = 0;
        resize = size*2;
        reused = 0;
        std::vector<std::list<KeyVal>> vec_rehash(resize);
        rehash = vec_rehash;
    }
    //标志不为-1,代表rehash正在使用,将数据添加到rehash表,并进行数据迁移.
    if(rehashhidx != -1){
        std::cout << " resize: " <<resize <<std::endl;
        if(resize == 0){
            return;
        }
        rehash[key%resize].push_front(rhs);
        reused++;
        StormDBRehash();
    }else{
        hash[key%size].push_front(rhs);
        used++;
    }
}
bool 
StormDB::StormDBDel(std::string rhs){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int hash_key = GetKey_char(a);
    delete[] a;
    //若hash表的大小是使用量的十倍则用rehash表进行hash表减少空间的操作. 
    if((used != 0) && (size/used >= 10) && (rehashhidx == -1)){
        std::cout << "delete" <<std::endl;
        rehashhidx = 0;
        resize = size / 2;
        reused = 0;
        std::vector<std::list<KeyVal>>vec_rehash(resize);
        rehash = vec_rehash;
    }
    //在rehash表中进行delete操作
    if(rehashhidx != -1){
        std::cout << "delete : rehashhidx" <<std::endl;
        auto item = rehash[hash_key % resize].begin();
        while(item != rehash[hash_key % resize].end()){
            if(rhs == (*item).GetKey()){
                hash[hash_key % resize].erase(item);
                reused--;
                StormDBRehash();
                return true;
            }else{
                item++;
            }
        }
        StormDBRehash();
    }
    auto item = hash[hash_key % size].begin();
    while(item != hash[hash_key % size].end()){
        if(rhs == (*item).GetKey()){
            hash[hash_key % size].erase(item);
            used--;
            return true;
        }else{
            item++;
        }
    }
    return false;

}
void
StormDB::StormDBDestory(){
    //用swap的方法对vector容器进行销毁工作(因为clear函数无法减少容器进行的我预分配)
    std::vector<std::list<KeyVal>>().swap(hash);
    std::vector<std::list<KeyVal>>().swap(rehash);

    //重新对hash表进行初始化
    std::vector<std::list<KeyVal>> vec(HASH_MIN);

    used = 0;
    size = HASH_MIN;
    hash = vec;
    resize = 0;
    reused = 0;
    rehashhidx = -1;
}
bool
StormDB::StormDBFind(std::string rhs){
    printf("Find执行了\n");
    char *a = new char[rhs.size() + 10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item : hash[key % size]){
        if(rhs == item.GetKey()){
            return true;
        }
    }
    if(rehashhidx != -1){
        for(auto item : rehash[key % resize]){
            if(rhs == item.GetKey()){
                return true;
            }
        }
    }
    return false;
}
bool
StormDB::StormDBTypeCompare(std::string rhs,int type){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;

    for(auto item : hash[key%size]){
        if(rhs == item.GetKey()){
            if(type == item.GetType()){
                return true;
            }
            return false;
        }
    }
    if(rehashhidx != -1){
        for(auto item : rehash[key % resize]){
            if(rhs == item.GetKey()){
                if(type == item.GetType()){
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
unsigned int
StormDB::StormDBSize(){
    return used+reused;
}
bool 
StormDB::StormDB_Value_Add(std::string rhs,void *obj){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int  key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).KeyValAdd(obj);
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).KeyValAdd(obj);
                return true;
            }
        }
    }
    return false;
}
int StormDB::StormDB_Value_Append(std::string rhs,void *obj){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            
           return (*item).KeyValueAppend(obj);
        
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % size].begin();item != rehash[key % size].end();item++){
            if(rhs == (*item).GetKey()){
              return  (*item).KeyValueAppend(obj);
            }
            
        }
    }
    return -1;
}
bool
StormDB::StormDB_Value_Del(std::string rhs,void *obj){
    char *a=new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete []a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            if((*item).KeyValDel(obj) == false){
                return false;
            }
            if(StormDBFind(rhs)){
            printf("find\n");
            printf("%u\n",StormDB_Value_Size(rhs));
            if(StormDB_Value_Size(rhs) == 0){
                StormDBDel(rhs);
                return true;
            }
    }
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                if((*item).KeyValDel(obj) == false){
                    return false;
                }
                if(StormDBFind(rhs)){
                printf("find\n");
                printf("%u\n",StormDB_Value_Size(rhs));
                if(StormDB_Value_Size(rhs) == 0){
                    StormDBDel(rhs);
                    return true;
        }
    }
                return true;
            }
        }
    }
    return false;
}
bool StormDB::StormDB_Value_Value(std::string rhs,void *buff){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key%size].begin();item != hash[key%size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).KeyValue(buff);
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).KeyValue(buff);
                return true;
            }
        }
    }
    return true;
}
bool 
StormDB::StormDB_Value_Destory(std::string rhs){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).KeyValDestory();
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).KeyValDestory();
                return true;
            }
        }
    }
    return false;
}
unsigned int
StormDB::StormDB_Value_Size(std::string rhs){
    char *a = new char[rhs.size() + 10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            return (*item).KeyValSize();
        }
    }
    if(rehashhidx != -1){
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                return (*item).KeyValSize();
            }
        }
    }
    return 0;

}
bool
StormDB::StormDBAddTime(std::string rhs,long long time){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).AddCutTime(time);
            return true;
        }
    }
    if(rehashhidx == -1){
        StormDBRehash();
        for(auto item = rehash[ key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).AddCutTime(time);
                return true;
            }
        }
    }
    return false;
}
bool
StormDB::StormDBAddPtime(std::string rhs,long long time){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item =hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).AddCutPtime(time);
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).AddCutPtime(time);
                return true;
            }
        }
    }
    return false;
}
bool 
StormDB::StormDBSetTime(std::string rhs,long long time){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).SetCutTime(time);
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).SetCutTime(time);
                return true;
            }
        }
    }
    return false;
}
bool StormDB::StormDBSetPtime(std::string rhs,long long time){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            (*item).SetCutPtime(time);
            return true;
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                (*item).SetCutPtime(time);
                 return true;
            }
        }
    }
    return false;
}
long long StormDB::StormDBGetTime(std::string rhs){
    char *a = new char[rhs.size()+10];
    StormDB_CStr(a,rhs);
    unsigned int  key = GetKey_char(a);
    delete[] a;
    for(auto item = hash[key % size].begin();item != hash[key % size].end();item++){
        if(rhs == (*item).GetKey()){
            return (*item).GetCutTime();
        }
    }
    if(rehashhidx != -1){
        StormDBRehash();
        for(auto item = rehash[key % resize].begin();item != rehash[key % resize].end();item++){
            if(rhs == (*item).GetKey()){
                return (*item).GetCutTime();
            }
        }
    }

}
char *StormDB::StormDB_CStr(char *a,std::string rhs){
     strcpy(a,rhs.c_str());
    for(int i = rhs.size(); i < rhs.size()+10;i++){
        a[i] = 0;
    }
    return a;
}
void StormDB::StormDB_Show(){
    std::cout << "hash: "<<std::endl;
    std::cout << "size: "<<size << " used: "<<used << " hash_size: "<<hash.size() <<std::endl;
    int i = 0;
    for(auto item : hash){
        std::cout <<"item.size: "<< item.size() <<std::endl;
        for(auto it : item){
            std::cout << i << " : "<<std::endl;
            std::cout << it.GetKey()<<"-----"<<it.GetHash()<<std::endl;
        }
        i++;
    }
    std::cout << "rehash: "<<std::endl;
    std::cout << "resize: "<<resize << " reused: "<< reused <<" rehash_size: "<<rehash.size() <<std::endl;
    i = 0;
    for(auto item : rehash){
        for(auto it : item){
            std::cout << i << " : "<<std::endl;
            std::cout << it.GetKey() << "----"<<it.GetHash() <<std::endl; 
        }
        i++;
    }
    std::cout << "rehashhidx: "<< rehashhidx <<std::endl;
    std::cout << "rehash_default: "<< rehash_default <<std::endl;
    std::cout << "-----------------------------"<<std::endl;
}
unsigned int 
StormDB::GetKey_int(unsigned int key){
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key >> 3);
    key ^= (key >> 6);
    key += (key << 11);
    key ^= (key >> 16);
    return key;
}
unsigned int StormDB::GetKey_char(const void  *key){
    uint32_t seed = 5635;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    int len = 8;
    uint32_t h = seed ^ len;
    const unsigned char * data = (const unsigned char *)key;

    while(len >= 4){
        uint32_t k = *(uint32_t *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }
    switch(len){
        case 3:h ^= data[2] << 16;
        case 2:h ^= data[1] << 8;
        case 1:h ^= data[0];
        h *= m;
    }
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return (unsigned int)h;
}

