/*************************************************************************
	> File Name: StormDB_DB.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月18日 星期三 14时44分28秒
 ************************************************************************/

#ifndef _STORMDB_DB_H
#define _STORMDB_DB_H
#include <iostream>
#include <list>
#include <vector>
#include "./StormDB_KV.h"
class StormDB{
    unsigned long used;
    unsigned long size;
    std::vector<std::list<KeyVal>> hash;
    unsigned long reused;
    unsigned long resize;
    std::vector<std::list<KeyVal>> rehash;
    int rehashhidx;
    int  rehash_default;
public:
    StormDB(int hashsize,int rehashsize);
    ~StormDB() = default;
    void StormDBAdd(KeyVal rhs);
    bool StormDBDel(std::string rhskey);
    void StormDBRehash();
    void StormDBUpdate(KeyVal rhs);
    void StormDBDestory(); //删除整个hash表
    bool StormDBFind(std::string); 
    bool StormDBTypeCompare(std::string rhs,int type);
    unsigned int StormDBSize(); 


    bool StormDB_Value_Add(std::string rhs,void *obj);
    int StormDB_Value_Append(std::string rhs,void *obj);
    bool StormDB_Value_Del(std::string rhs,void *obj);
    bool StormDB_Value_Value(std::string rhs,void *buff);
    bool StormDB_Value_Destory(std::string rhs); //删除某个键值对.

    unsigned int StormDB_Value_Size(std::string rhs);
    bool StormDBAddTime(std::string rhs,long long time);
    bool StormDBAddPtime(std::string rhs,long long time);
    bool StormDBSetTime(std::string rhs,long long time);
    bool StormDBSetPtime(std::string rhs,long long time);
    long long StormDBGetTime(std::string rhs);

    char* StormDB_CStr(char *a,std::string rhs);
    void StormDB_Show(); //测试
    unsigned int GetKey_int(unsigned int key);
    unsigned int GetKey_char(const void *key);
};
#endif
