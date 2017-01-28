/*************************************************************************
	> File Name: StormDB_DBAll.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月19日 星期四 11时34分45秒
 ************************************************************************/

#ifndef _STORMDB_DBALL_H
#define _STORMDB_DBALL_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include "./StormDB_DB.h"
#include "./StormDB_KV.h"
#include "./StormDB_Utils.hpp"
#include <sstream>
class StormDBAll{
private:
    typedef char* (StormDBAll::*fun)(char*,char*,char*);
    int max_num;
    std::vector<StormDB> DB;

    bool StormDBAllAdd(std::string keyname,void  *obj,int typedata,int dbnum = 0);
    bool StormDBAllValueDel(std::string keyname,void *obj,int typedata,int dbnum = 0);
    int StormDBAllAppend(std::string keyname,void *obj,int typedata,int dbnum = 0);
    bool StormDBAllDel(std::string keyname,int dbnum = 0);
    bool StormDBAllValue(std::string keyname,void *buff,int typedata,int dbnum = 0);

    bool Add(char *key,char *valkey,int typedata,char *value,int dbnum = 0);
    bool Add(char *key,char *valkey,int typedata,int dbnum = 0);
    bool ValDel(char *key,int typedata,char *valkey =" ",int dbnum = 0);
    bool Del(const char *key,int dbnum = 0);
    const char* Value(const char *key,int typedata,int dbnum = 0);
    bool Find(const char *key,int dbnum = 0);
    int ValAppend(const char *key,int typedata,char *value);
    void StormDBAll_Show();
    void StormDBAll_Destory(int num = 0);
    void StormDBAll_Destory();

    bool StormDBAll_Add_Time(std::string rhs,long long time ,int dbnum = 0);
    bool StormDBAll_Add_Ptime(std::string rhs,long long time,int dbnum = 0);
    bool StormDBAll_Set_Time(std::string rhs,long long time,int dbnum = 0);
    bool StormDBAll_Set_Ptime(std::string rhs,long long time,int dbnum = 0);
    long long StormDBAll_GetTime(std::string rhs,int dbnum = 0);

    void StormDBAll_Show(int dbnum = 0);
    int StormDBAllGetNum();

    char* HSET(char *key,char *valkey,char * value);
    char* HDEL(char *key,char *valkey,char *value);
    char* HGETALL(char *key,char *valkey,char *value);
    char* DEL(char *key,char *valkey,char *value);
    char* SET(char *key,char *valkey,char *value);
    char* GET(char *key,char *valkey,char *value);
    char* APPEND(char *key,char *valkey,char *value);
    char* LSET(char *key,char *valkey,char *value);
    char* LGET(char *key,char *valkey,char *value);
    char* LPUSH(char *key,char *valkey,char *value);
    char* LPOP(char *key,char *valkey, char *value);
    char* RPUSH(char *key,char *valkey,char *value);
    char* RPOP(char *key,char *valkey,char *value);
    void IntToString(int t,std::string &str){
        std::stringstream ss;
        ss << t;
        ss >> str;
        
    }
public:
    StormDBAll(int num,int hash,int rehash);
    ~StormDBAll() = default;
    char* handle(std::string signal,std::string key,std::string valuekey,std::string value);
    char* handle(std::vector<std::string> &items);
};
#endif
