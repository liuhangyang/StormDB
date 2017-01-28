/*************************************************************************
	> File Name: StormDB_KV.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 21时02分57秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_KV.h"
using namespace std;
KeyVal::KeyVal(std::string keyname,int typedata,int elem){
    key = keyname;
    type = typedata;
    hashkey = 0;
    cuttime = -1;
    ServerId = elem;
    if(typedata == Hash_Map_pseudo_NUM){
        value = new HashDictHt<std::string>;
    }else if(typedata == Hash_Map_NUM){
        value = new Hashmap<std::string>;
    }else if(typedata == Ziplist_NUM){
        value = new Ziplist<std::string>;
    }else if(typedata == String_NUM){
        value = new String;
    }else if(typedata == Stack_NUM){
        value = new Stack<std::string>;
    }else if(typedata == Queue_NUM){
        value = new Queue<std::string>;
    }else if(typedata == INT_NUM){
        value = new Intset; 
    }
}
KeyVal::KeyVal(const KeyVal &a){
    key = a.key;
    type = a.type;
    hashkey = a.hashkey;
    cuttime = a.cuttime;
    ServerId = a.ServerId;

    if(type == Hash_Map_pseudo_NUM){
        value = new HashDictHt<std::string>;
        (*(HashDictHt<std::string> *)value) = (*(HashDictHt<std::string> *)a.value);
   
    }else if(type == Hash_Map_NUM){
        value = new Hashmap<std::string>;
        (*(Hashmap<std::string>*)value) = (*(Hashmap<std::string> *)a.value);
    
    }else if(type == Ziplist_NUM){
        value = new Ziplist<std::string>;
        (*(Ziplist<std::string> *)value) = (*(Ziplist<std::string> *)a.value);
    
    }else if(type == String_NUM){
        value = new String;
        (*(String *)value) = (*(String *)a.value);
    
    }else if(type == Stack_NUM){
        value = new Stack<std::string>;
        (*(Stack<std::string> *)value) = (*(Stack<std::string> *)a.value);
    
    }else if(type == Queue_NUM){
        value = new Queue<std::string>;
        (*(Queue<std::string> *)value) = (*(Queue<std::string >*)a.value);
    }else if(type == INT_NUM){
        value = new Intset;
        (*(Intset*)value) = (*(Intset*)a.value);
    }
    
}
KeyVal::~KeyVal(){
    if(type == Hash_Map_pseudo_NUM){
       
        delete (HashDictHt<std::string> *)value;
    }else if(type == Hash_Map_NUM){
        delete (Hashmap<std::string>*)value;
    
    }else if(type == Ziplist_NUM){
        value = new Ziplist<std::string>;
        delete (Ziplist<std::string> *)value;
    
    }else if(type == String_NUM){
        delete (String *)value;
    
    }else if(type == Stack_NUM){
        delete (Stack<std::string> *)value; 
    
    }else if(type == Queue_NUM){
        delete (Queue<std::string> *)value;
    }else if(type == INT_NUM){
        delete (Intset *)value;
    }
    
}
void
KeyVal::KeyValAdd(void *obj){
    if(type == Hash_Map_pseudo_NUM){
        (*(HashDictHt<std::string>*)value).HashDictHtSet(*(HashEntry<std::string>*)obj);
        if(KeyValSize() == (HASH_DEFAULT / 2)){
            HashDictHt<std::string> hashPseudo;
            hashPseudo = (*(HashDictHt<std::string>*)value);
            type = Hash_Map_NUM;
            delete (HashDictHt<std::string> *)value;
            value = new Hashmap<std::string>(hashPseudo);
        }
    }else if(type == Hash_Map_NUM){
        (*(Hashmap<std::string> *)value).HashMapAdd(*(HashEntry<std::string>*)obj);
    }else if(type == Ziplist_NUM){
        (*(Ziplist<std::string>*)value).Ziplist_add(*(std::string *)obj);
    }else if(type == String_NUM){
        (*(String *)value) = (*(String *)obj);
    }else if(type == Stack_NUM){
        (*(Stack<std::string> *)value).StackPush(*(std::string *)obj);
    }else if(type == Queue_NUM){
        (*(Queue<std::string> *)value).QueuePush(*(std::string *)obj);
    }else if(type == INT_NUM){
        //(*(Intset*)value).Insert(*)
    }
}
int KeyVal::KeyValueAppend(void *obj){
    (*(String*)value) += (*(String *)obj);
    return (*(String *)value).getSize();
}
bool KeyVal::KeyValDel(void *obj){
    if(type == Hash_Map_pseudo_NUM){
        if(((*(HashDictHt<std::string>*)value).HashDictHtTest((*(HashEntry<std::string> *)obj).HashKey())) == false){
            return false;
        }
        (*(HashDictHt<std::string> *)value).HashDictHtDel((*(HashEntry<std::string> *)obj).HashKey());
        return true;
    }else if(type == Hash_Map_NUM){
        if((*(Hashmap<std::string> *)value).HashMapFind(*(HashEntry<std::string> *)obj) == false){
            return false;
        }
        (*(Hashmap<std::string> *)value).HashMapDel(*(HashEntry<std::string >*)obj);
        return true;
    }else if( type ==Ziplist_NUM){
        
        if((*(Ziplist<std::string>*)value).Ziplist_find(*(std::string *)obj) == false){
            return false;
        }
        std::cout << "删除"<<std::endl;
        (*(Ziplist<std::string> *)value).Ziplist_del(*(std::string *)obj);
        std::cout <<"sucess" <<endl;
           return true;
    }else if(type == Stack_NUM){
        if((*(Stack<std::string> *)value).StackIsEmpty() == true){
            return false;
        }
        (*(Stack<std::string> *)value).StackPop();
        return true;
    }else if(type == Queue_NUM){
        if((*(Queue<std::string> *)value).QueueIsEmpty() == true){
            return false;
        }
        (*(Queue<std::string> *)value).QueuePop();
        return true;
    }

}
void
KeyVal::KeyValue(void *buff){
    if(type == Hash_Map_pseudo_NUM){
        (*(std::vector<HashEntry<std::string>> *)buff) = 
        (*(HashDictHt<std::string> *)value).HashDictHtData();
    }else if(type == Hash_Map_NUM){
        (*(std::vector<HashEntry<std::string>> *)buff) =
        (*(Hashmap<std::string> *)value).HashMapAll();
    }else if(type == Ziplist_NUM){
        (*(std::vector<std::string> *)buff) = (*(Ziplist<std::string> *)value).Ziplist_return();
    }else if(type == String_NUM){
        (*(String *)buff) = (*(String *)value);
    }else if(type == Stack_NUM){
        (*(string *)buff) = (*(Stack<std::string> *)value).StackTop();
    }else if(type == Queue_NUM){
        (*(string *)buff) = (*(Queue<std::string> *)value).QueueFront();
    }
}
void
KeyVal::KeyValDestory(){
    if(type == Hash_Map_pseudo_NUM){
        (*(HashDictHt<std::string> *)value).HashDictHtDestory();
    }else if(type == Hash_Map_NUM){
        (*(Hashmap<std::string> *)value).HashMapDestory();
    }else if(type == Ziplist_NUM){
        (*(Ziplist<std::string> *)value).Ziplist_destory();
    }else if(type == Stack_NUM){
        (*(Stack<std::string> *)value).StackDestory();
    }else if(type == Queue_NUM){
        (*(Queue<std::string> *)value).QueueDestory();
    }
}
int
KeyVal::KeyValSize(){
    if(type == Hash_Map_pseudo_NUM){
        return (*(HashDictHt<std::string> *)value).HashDictHtSize();
    }else if(type == Hash_Map_NUM){
        return (*(Hashmap<std::string> *)value).HashMapSize();
    }else if(type == Ziplist_NUM){
        return (*(Ziplist<std::string> *)value).Ziplist_size();
    }else if(type == Stack_NUM){
        return (*(Stack<std::string> *)value).StackSize();
    }else if(type == Queue_NUM){
        return (*(Queue<std::string> *)value).QueueSize();
    }
}
void
KeyVal::AddCutTime(long long time){
    AddCutPtime(1000 * time);
}
void 
KeyVal::AddCutPtime(long long time){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    time += (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    
}
void 
KeyVal::SetCutTime(long long time){
    SetCutPtime(time * 1000);
}
void
KeyVal::SetCutPtime(long long time){
    cuttime = time;
}
void
KeyVal::SetHashKey(unsigned int hash){
    hashkey = hash;
}
int
KeyVal::GetType(){
    return type;
}
unsigned int 
KeyVal::GetHash(){
    return hashkey;
}
std::string 
KeyVal::GetKey(){
    return key;
}
long long
KeyVal::GetCutTime(){
    return cuttime;
}




