/*************************************************************************
	> File Name: StormDB_Judge.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月22日 星期日 11时26分40秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Judge.h"
std::pair<std::string,int> pairArray[]=
{
    std::make_pair("SET",2),
    std::make_pair("GET",1),
    std::make_pair("HGETALL",1),
    std::make_pair("DEL",1),
    std::make_pair("HSET",3),
    std::make_pair("HDEL",2),
    std::make_pair("LSET",2),
    std::make_pair("LGET",1),
    std::make_pair("LPUSH",2),
    std::make_pair("LPOP",1),
    std::make_pair("RPUSH",2),
    std::make_pair("RPOP",1),
    std::make_pair("INCR",1),
    std::make_pair("DECR",1),
    std::make_pair("APPEND",2),
    std::make_pair("QUIT",0)
};
StrInt Judge::CmdMap(pairArray,pairArray + sizeof(pairArray)/sizeof(pairArray[0]));
const char*
Judge::JudgeCommand(std::string key,int t){
    std::string str("");
    toUpper1(key);
    if(CmdMap.count(key) > 0){
        if(CmdMap[key] == t){
            return "OK";
        }else{
            str += "(error) ERR wrong number of argment for ";
            str += "'";
            str += key;
            str += "'";
            str += "command";
            return str.c_str();
        }
    }else{
        str += "(error) ERR unknown command '";
        str += key;
        str += "'";
        return str.c_str();
    }
}
