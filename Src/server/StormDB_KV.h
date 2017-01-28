/*************************************************************************
	> File Name: StormDB_KV.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月17日 星期二 20时36分10秒
 ************************************************************************/

#ifndef _STORMDB_KV_H
#define _STORMDB_KV_H
#include <iostream>
#include <string>
#include "./StormDB_Data_num.h"
#include "./StormDB_Hash_Map.h"
#include "./StormDB_Ziplist.h"
#include "./StormDB_String.h"
#include "./StormDB_Queue.h"
#include "./StormDB_Stack.h"
#include "./StormDB_intset.h"
#include <sys/time.h>

#define TIME_DONE -1
class KeyVal{
private:
    std::string key;
    void *value;
    int type;
    unsigned int hashkey;
    long long cuttime;
    int ServerId;
public:
    KeyVal() = default;
    KeyVal(std::string keyname,int typeData,int elem);
    KeyVal(const KeyVal &a);
    ~KeyVal();
    void KeyValAdd(void *obj);
    int KeyValueAppend(void *obj);
    bool KeyValDel(void *obj);
    void KeyValue(void *buff);
    void KeyValDestory();
    void KeyValFlag();
    int KeyValSize();
    void AddCutTime(long long time);
    void AddCutPtime(long long time);
    void SetCutTime(long long time);
    void SetCutPtime(long long time);
    void SetHashKey(unsigned int hash);
    int GetType();
    unsigned int GetHash();
    std::string GetKey();
    long long GetCutTime();
};
#endif
