/*************************************************************************
	> File Name: StormDB_Client.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 21时09分02秒
 ************************************************************************/

#ifndef _STORMDB_CLIENT_H
#define _STORMDB_CLIENT_H
#include <stdio.h>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <unistd.h>
#include "./StormDB_Command.hpp"
#include "./StormDB_Judge.h"
#include "./StormDB_Error.hpp"
#include "./StormDB_Utils.hpp"
#define IP "127.0.0.1"
#define PORT  8888
struct key_value{
    std::string key;
    std::string val;
};
struct key_score{
    std::string key;
    int score;
};
typedef std::vector<std::string> string_vector;
typedef std::vector<key_score> key_score_vector;
typedef std::set<std::string>  string_set;
typedef std::map<std::string,std::string> string_map;
typedef std::map<std::string,int> StrToInt;
class Client{
public:
    explicit Client(void);
    explicit Client(const std::string &host);
    explicit Client(const std::string &host,int port);
    ~Client(void);
    bool opend(void) const;
    int id(void) const {
        return _socket;
    }
    void set(const std::vector<std::string> &data);
    //std::string get(const std::vector<std::string> &data);
    void get(const std::vector<std::string> &data);
    void del(const std::vector<std::string> &data);
    //long append(const std::vector<std::string> &data);
    void append(const std::vector<std::string> &data);
    //bool hset(const std::vector<std::string> &data);
    void hset(const std::vector<std::string> &data);
    //bool get(const std::vector<std::string> &data);
    void hdel(const std::vector<std::string> &data);
    void hgetall(const std::vector<std::string> &data,string_vector &fields,string_vector &values);
    void lset(const std::vector<std::string> &data);
    //std::string lget(const std::vector<std::string> &data);
    void lget(const std::vector<std::string> &data);
    void lpush(const std::vector<std::string> &data);
    //std::string lpop(const std::vector<std::string> &data);
    void lpop(const std::vector<std::string> &data);
    
    void rpush(const std::vector<std::string> &data);
    //std::string rpop(const std::vector<std::string> &data);
    void rpop(const std::vector<std::string> &data);
    
    void incr(const std::vector<std::string> &data);
    //long incr(const std::vector<std::string> &data);
    void decr(const std::vector<std::string> &data);
    //long decr(const std::vector<std::string> &data);
    void _send(const std::string &data);
    
    bool input(std::vector<std::string> &str);
    void toUpper(std::string& str){
        for(int i = 0;i<str.length();i++){
            if(str[i] > 96 && str[i] < 123){
                str[i] -= 32;
            } 
        }
    }
    void start();
    std::string intToByte(int length);
private:
    void _init(const std::string &host,int port);
    void _recv_ok_reply();
    void _recv_string_reply();
    //long _recv_multi_bulk_reply(all);
    void _recv_int_reply();
    void _recv_rlpop_reply();
    void _recv_multi_bulk_reply(string_vector all);
private:
    int _socket;
    static StrToInt IntMap;


};
#endif
