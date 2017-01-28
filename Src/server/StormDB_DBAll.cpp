/*************************************************************************
	> File Name: StormDB_DBAll.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月19日 星期四 11时21分29秒
 ************************************************************************/
#include "./StormDB_DBAll.h"
#include <fstream>
#include<stdio.h>
#include <iostream>
using namespace std;
StormDBAll::StormDBAll(int num,int hash,int rehash){
    max_num = num;
    for(int i = 0;i < num;i++){
        DB.push_back(StormDB(hash,rehash));
    }
}
void 
StormDBAll::StormDBAll_Show(){
    for(auto item : DB){
        item.StormDB_Show();
    }
}
void 
StormDBAll::StormDBAll_Destory(int dbnum){
    DB[dbnum].StormDBDestory();
}
void
StormDBAll::StormDBAll_Destory(){
    for(auto item = DB.begin();item != DB.end();item++){
        (*item).StormDBDestory();
    }
}
bool StormDBAll::StormDBAllAdd(std::string keyname,void *obj,int typedata,int dbnum){
    if(DB[dbnum].StormDBFind(keyname) == true){
        if(DB[dbnum].StormDBTypeCompare(keyname,typedata) == false){
            return false;
        }else{
            DB[dbnum].StormDB_Value_Add(keyname,obj);
        }
    }else{
        KeyVal k(keyname,typedata,dbnum);
        DB[dbnum].StormDBAdd(k);
        DB[dbnum].StormDB_Value_Add(keyname,obj);
    }
    return true;
}
int StormDBAll::StormDBAllAppend(std::string keyname,void *obj,int typedata,int dbnum){

    if(DB[dbnum].StormDBFind(keyname) == true){
        if(DB[dbnum].StormDBTypeCompare(keyname,typedata)== false){
            return -1;
        }else{
            return DB[dbnum].StormDB_Value_Append(keyname,obj);
        }
    }else{
        KeyVal k(keyname,typedata,dbnum);
        DB[dbnum].StormDBAdd(k);
        DB[dbnum].StormDB_Value_Add(keyname,obj);
        return 0;
    }
}
bool StormDBAll::StormDBAllValueDel(std::string keyname,void *obj,int typedata,int dbnum){
    if(DB[dbnum].StormDBTypeCompare(keyname,typedata) == true){
        if(DB[dbnum].StormDB_Value_Del(keyname,obj)){
            return true;
        }else{
            printf("------------------------------------>\n");
            return false;
        }
    }
    return false;
} 
bool StormDBAll::StormDBAllDel(std::string rhskey,int dbnum){
    if(Find(rhskey.c_str()) == true){
        if(DB[dbnum].StormDBDel(rhskey)){
            return true;
        }else{
            return false;
        }
    }
    return false;
}
bool
StormDBAll::StormDBAllValue(std::string keyname,void *buff,int typedata,int dbnum){
    if(DB[dbnum].StormDBTypeCompare(keyname,typedata) == true){
        DB[dbnum].StormDB_Value_Value(keyname,buff);
        return true;
    }
    return false;
}
bool
StormDBAll::Add(char *key,char *valkey,int typedata,char *value,int dbnum){
    if((typedata == Hash_Map_pseudo_NUM) || (typedata == Hash_Map_NUM)){
        void *obj = new HashEntry<std::string>;
        std::string keyAll(key);
        String StrValKey(valkey);
        std::string StrValue(value);
        HashEntry<std::string> hmp(StrValKey,StrValue);
        (*(HashEntry<std::string> *)obj) = hmp;

        if(StormDBAllAdd(keyAll,obj,typedata,dbnum) == false){
            delete (HashEntry<string> *)obj;
            return false;
        }
        delete (HashEntry<string> *)obj;
    }
    return true;
}
bool StormDBAll::Add(char *key,char *valkey,int typedata,int dbnum){
    if((typedata == Ziplist_NUM) || (typedata == Stack_NUM) || (typedata == Queue_NUM)){
        void *obj = new std::string;
        std::string keyAll(key);
        std::string StrValue(valkey);
        (*(std::string *)obj) = StrValue;
        if(StormDBAllAdd(keyAll,obj,typedata,dbnum) == false){
            delete (std::string *)obj;
            return false;
        }
        delete (std::string *)obj;
    }else if(typedata == String_NUM){
        void *obj = new String;
        std::string keyAll(key);
        String StrValue(valkey);
        (*(String *)obj) = StrValue;
        if(StormDBAllAdd(keyAll,obj,typedata,dbnum) == false){
            delete (String *)obj;
            return false;
        }
        delete (String *)obj;
    }
    return true;
}
bool StormDBAll::ValDel(char *key,int typedata,char *valkey,int dbnum){
    if((typedata == Hash_Map_pseudo_NUM) || (typedata == Hash_Map_NUM)){
        void *obj = new HashEntry<std::string>;
        std::string keyAll(key);
        String StrValKey(valkey);
        HashEntry<std::string> hmp(StrValKey," ");
        (*(HashEntry<std::string>*)obj) = hmp;
        if(StormDBAllValueDel(keyAll,obj,typedata,dbnum) == false){
            delete (HashEntry<std::string> *)obj;
            return false;
        }
        delete (HashEntry<std::string> *)obj;
    }else if(typedata == Ziplist_NUM){
        void *obj = new std::string;
        std::string keyAll(key);
        std::string StrValue(valkey);
        (*(std::string *)obj) = StrValue;
        if(StormDBAllValueDel(keyAll,obj,typedata,dbnum) == false){
            delete (std::string *)obj;
            return false;
        }
        delete (std::string *)obj;
    }else if((typedata == Stack_NUM) || (typedata == Queue_NUM)){
        void *obj;
        std::string keyAll(key);
        if(StormDBAllValueDel(keyAll,obj,typedata,dbnum) == false){
            return false;
        }
    }
    return true;
}
bool StormDBAll::Del(const char *key,int dbnum){
    std::string keyAll(key);
    if(StormDBAllDel(keyAll,dbnum) == false){
        return false;
    }
    return true;
}
const char* StormDBAll::Value(const char *key,int typedata,int dbnum){
    if((typedata == Hash_Map_pseudo_NUM) || (typedata == Hash_Map_NUM)){
        void *buff = new std::vector<HashEntry<std::string>>;
        std::string keyAll(key);
        std::string str("");
        if(StormDBAllValue(keyAll,buff,typedata,dbnum) == false){
            delete (std::vector<HashEntry<std::string>> *)buff;
            return "(nil)\r\n";
        }
        for(auto item : (*(std::vector<HashEntry<std::string>> *)buff)){ 
            str += item.HashKey().StringGetChar();
            str += "\r\n";
            str += item.HashValue();
            str += "\r\n";
            //str += "\"";
        }
        /*std::vector<std::string> items;
        rtrim(str);
        split(str.c_str(),"\r\n",items);
        std::cout << "items:" <<items.size()<<std::endl;
        for(auto i : items){
            std::cout << "  "<< i<< " ddd ";
        }
        std::cout << "yanglongfei" << std::endl;
        ofstream out;
        out.open("output.txt");
        out << str.c_str()<<flush;
       out.close();*/
        return str.c_str();
    }else if(typedata == Ziplist_NUM){
        void *buff = new std::vector<std::string>;
        std::string str("");
        std::string keyAll(key);
        if(StormDBAllValue(keyAll,buff,typedata,dbnum) == false){
            delete (std::vector<std::string> *)buff;
            return "(nil)\r\n";
        }
        for(auto item : (*(std::vector<std::string> *)buff)){
            std::string s("");
            IntToString(item.size(),s);
            str += "$";
            str += s;
            str += "\r\n";
            str += item;
            str += "\r\n";
        }
        delete (std::vector<std::string> *)buff;
        return str.c_str();
    }else if(typedata == String_NUM){
        void *buff = new String;
        std::string keyAll(key);
        if(StormDBAllValue(keyAll,buff,typedata,dbnum) == false){
            delete (String *)buff;
            return "(nil)\r\n";
        }
        std::string str("");
        std::string ch = (*(String *)buff).StringGetChar();
        std::string s("");
        IntToString(ch.size(),s);
        str += "$";
        str += s;
        str += "\r\n";
        str += ch;
        ch += "\r\n";
        delete (String *)buff;
        return ch.c_str();
    }else if((typedata == Stack_NUM) || (typedata == Queue_NUM)){
        void *buff = new std::string;
        std::string keyAll(key);
        if(StormDBAllValue(keyAll,buff,typedata,dbnum) == false){
            delete (std::string *)buff;
            return "(nil)\r\n";
        }
        std::string str1("");
        std::string s("");
        string str = (*(std::string *)buff);
        IntToString(str.size(),s);
        str1 += "$";
        str1 += s;
        str1 += "\r\n";
        str1 += str;
        str1  += "\r\n";
        delete (std::string *)buff;
        return str1.c_str();
    }
}
int StormDBAll::ValAppend(const char *key,int typedata,char *value){
    std::string str(key);
    void *obj = new String;
    String Value(value);
    (*(String *)obj)=Value;
    return StormDBAllAppend(str,obj,typedata);
}
bool StormDBAll::Find(const char *key,int dbnum){
    std::string str(key);
    if(DB[dbnum].StormDBFind(str) == true){
        return true;
    }
    return false;
}
bool StormDBAll::StormDBAll_Add_Time(std::string rhs,long long time,int dbnum){
    if(DB[dbnum].StormDBFind(rhs) == true){
        DB[dbnum].StormDBAddTime(rhs,time);
        return true;
    }
    return false;
}
bool StormDBAll::StormDBAll_Add_Ptime(std::string rhs,long long time,int dbnum){
    if(DB[dbnum].StormDBFind(rhs) == true){
        DB[dbnum].StormDBAddPtime(rhs,time);
        return true;
    }
    return false;
}
bool StormDBAll::StormDBAll_Set_Time(std::string rhs,long long time,int dbnum){
    if(DB[dbnum].StormDBFind(rhs) == true){
        DB[dbnum].StormDBSetTime(rhs,time);
        return true;
    }
    return false;
}
bool StormDBAll::StormDBAll_Set_Ptime(std::string rhs,long long time,int dbnum){
    if(DB[dbnum].StormDBFind(rhs) == true){
        DB[dbnum].StormDBSetPtime(rhs,time);
        return true;
    }
    return false;
}
long long StormDBAll::StormDBAll_GetTime(std::string rhs,int dbnum){
    return DB[dbnum].StormDBGetTime(rhs);
}
void
StormDBAll::StormDBAll_Show(int dbnum){
    DB[dbnum].StormDB_Show();
}
int StormDBAll::StormDBAllGetNum(){
    return max_num;
}
char* StormDBAll::HSET(char* key,char* valkey,char* value){
    char *result;
    if(Add(key,valkey,1,value) == false){
        result = "-ERR hset error\r\n";
    }else {
        result = "+OK\r\n";
    }
    return result;
}
char* StormDBAll::HDEL(char *key,char *valkey,char *value){
    char *result;
    if(ValDel(key,1,valkey) == false){
        result = ":0\r\n";
    }else {
        result = ":1\r\n";
    }
    return result;
}
 char* StormDBAll::HGETALL(char* key,char* valkey,char* value){
    std::string Str("");
    const char *result;
    result = Value(key,1);
    char* b = new char[strlen(result)+1];
    bzero(b,sizeof(b));
    strcpy(b,result);
    if(strcmp(b,"(nil)\r\n") ==0){
         return b;
     }
     std::vector<std::string> items;
    rtrim(b);
    std::string str(b);
    split(str,"\r\n",items);
    std::string s;
    IntToString(items.size()-1,s);
    Str += "*";
    Str += s;
    Str+="\r\n";
    for(int i = 0;i < items.size()-1;i++){
        std::string s("");
        IntToString(items[i].size(),s);
        Str += "$";
        Str += s;
        Str += "\r\n";
        Str +=items[i];
        Str += "\r\n";
    }
    char* m = new char[Str.size()+1];
     strcpy(m,Str.c_str());
    return m;
}    
char* StormDBAll::DEL(char* key,char* valkey,char* value){
    char *result;
    if(Del(key)){

        result = ":1\r\n";
    }else{
        result = ":0\r\n";
    }
    return result;
}
char* StormDBAll::SET(char* key,char* valkey,char *value){
    char *result;
    if(Add(key,valkey,3) == false){
        result = "-ERR set error\r\n";
    }else{
        result = "+OK\r\n";
    }
    return result;
}
char* StormDBAll::GET(char* key,char* valkey,char* value){
    const char *result;
    result = Value(key,3);

    char* b = new char[strlen(result)+1];
    strcpy(b,result);
    return b;
}
char* StormDBAll::APPEND(char* key,char *valkey,char *value){
    int t = ValAppend(key,3,valkey);
    if(t == -1){
        return "-ERR append error\r\n";
    }else if(t == 0){
        return "+OK\r\n";
    }else {
        printf("t=======================++++:%d\n",t);
        char str1[20];
        bzero(str1,sizeof(str1));
        char *temp=":";
        char *str = new char[strlen(temp)+11];
        strcpy(str,temp);
        sprintf(str1,"%d",t);
        //sprintf(str1,"%s","\r\n");
        strcat(str1,"\r\n");
        strcat(str,str1);
        return str;
    }
} 
char* StormDBAll::LSET(char* key,char *valkey,char* value){
    char *result;
    if(Add(key,valkey,2) == false){
        result = "-ERR lset error\r\n";
    }else{
        result = "+OK\r\n";
    }
    return result;
}
char* StormDBAll::LGET(char* key,char *valkey,char *value){
    const char *result;
    result = Value(key,2);
    char* b = new char[strlen(result)+1];
    strcpy(b,result);
    return b;
}
char* StormDBAll::LPUSH(char* key,char* valkey,char* value){
    char *result;
    if(Add(key,valkey,4) == false){
        result = "-ERR lpush error\r\n";
    }else{
        result = "+OK\r\n";
    }
    return result;
}
char* StormDBAll::LPOP(char* key,char* valkey,char *value){
    const char *result;
    result = Value(key,4);

    char* b = new char[strlen(result)+1];
    strcpy(b,result);
    return b;
}
char* StormDBAll::RPUSH(char *key,char *valkey,char* value){
    char *result;
    if(Add(key,valkey,5) == false){
        result = "-ERR rpush error";
    }else{
        result = "+OK\r\n";
    }
    return result;
}
char* StormDBAll::RPOP(char* key,char* valkey,char* value){
    const char *a;
    a = Value(key,5);

    char* b = new char[strlen(a)+1];
    strcpy(b,a);
    return b;
}


char* StormDBAll::handle(std::string signal,std::string key,std::string valkey,std::string value){
    char *ret;
    map<std::string,fun> mp;
    mp.insert(pair<std::string,fun> ("HSET",&StormDBAll::HSET));
    //mp.insert(pair<std::string,fun> ("HGET",&StormDBAll::HGET));
    mp.insert(pair<std::string,fun> ("HDEL",&StormDBAll::HDEL));
    mp.insert(pair<std::string,fun> ("HGETALL",&StormDBAll::HGETALL));
    mp.insert(pair<std::string,fun> ("DEL",&StormDBAll::DEL));
    mp.insert(pair<std::string,fun> ("SET",&StormDBAll::SET));
    mp.insert(pair<std::string,fun> ("GET",&StormDBAll::GET));
    mp.insert(pair<std::string,fun> ("LSET",&StormDBAll::LSET));
    mp.insert(pair<std::string,fun> ("LGET",&StormDBAll::LGET));
    mp.insert(pair<std::string,fun> ("LPUSH",&StormDBAll::LPUSH));
    mp.insert(pair<std::string,fun> ("LPOP",&StormDBAll::LPOP));
    mp.insert(pair<std::string,fun> ("RPUSH",&StormDBAll::RPUSH));
    mp.insert(pair<std::string,fun> ("RPOP",&StormDBAll::RPOP));
    mp.insert(pair<std::string,fun> ("APPEND",&StormDBAll::APPEND));
    ret = (this->*mp[signal])((char*)key.c_str(),(char*)valkey.c_str(),(char*)value.c_str());
    
    //std::cout << "ret: " << ret <<std::endl;
    return ret;
}
char* StormDBAll::handle(std::vector<std::string> &items){
    if(items.size() == 8){
        printf("items[3]:%s\n,items[5]:%s\n",items[3].c_str(),items[5].c_str());   
        return handle(items[3],items[5],"\0","\0");
    } 
    if(items.size() == 10){
        printf("items[3]:%s\n,items[5]:%s\n,items[7]:%s\n",items[3].c_str(),items[5].c_str(),items[7].c_str());   
        return handle(items[3],items[5],items[7],"\0");
    }
    if(items.size() == 12){
        printf("items[3]:%s\n,items[5]:%s\n,items[7]:%s\n,items[9]:%s\n",items[3].c_str(),items[5].c_str(),items[7].c_str(),items[9].c_str());   
        return handle(items[3],items[5],items[7],items[9]);
    }
}



