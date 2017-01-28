/*************************************************************************
	> File Name: disServer.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月23日 星期一 15时08分44秒
 ************************************************************************/

#ifndef _DISSERVER_H
#define _DISSERVER_H
#include <map>
#include <stdio.h>
#include <pthread.h>
#include <functional>
#include <thread>
#include <assert.h>
#include <stdlib.h>
#include <memory>
#include <string>
#include <sstream>
#include "./Connection.h"
#include "./Client.h"
#include "Server.h"
#include "./StormDB_distributed_Hash.h"
#include "./StormDB_Utils.hpp"
#define MAXBUF 1024
using namespace eylib;
std::map<std::string,int> senWriteMap; //这个是服务器send,可写的大于实际发送的数据时，注册可写事件，写回调时从此map中查询未发送完成对象是哪个
int clientId = 0;
std::shared_ptr<CMD5HashFunc> pFunc(new CMD5HashFunc());
CConHash conhash(pFunc);
    std::map<std::string,std::shared_ptr<eylib::Connection>> clientMap;
    void messagecallback(std::shared_ptr<eylib::Connection> p,int m);
    void connectioncallback(std::shared_ptr<eylib::Connection> p);
    void closecallback(std::shared_ptr<eylib::Connection> p);
    void writecallback(std::shared_ptr<eylib::Connection> p);
    
    void Clientmessagecallback1(std::shared_ptr<ClientConnect> p,int m);
    void Clientconnectioncallback1(std::shared_ptr<ClientConnect> p);
    void Clientclosecallback1(std::shared_ptr<ClientConnect> p);
    void Clientwritecallback1(std::shared_ptr<ClientConnect> p);
    void getClientId(std::string& str){
        std::stringstream ss;
        ss << clientId;
        std::string s;
        ss >> s;
        str += s;
        clientId ++;
    }
    const char* getKey(const std::string &str){
        std::vector<std::string> items;
        split(str,"\r\n",items);
        return items[2].c_str();
    }
    const char* getName(const std::string &str){
        std::vector<std::string> items;
        split(str,"\r\n",items);
        /*for(auto i : items){
            std::cout << i<< std::endl;
        }*/
        return items[0].c_str();
    }
    void getClientData(const std::string &str,std::string &Str){
        std::vector<std::string> items;
        split(str,"\r\n",items);
        for(int i=1;i<items.size();i++){
            Str+=items[i];
            if(i != items.size()-1){
             Str+="\r\n";
            }
        }
    }
    std::string intToByte(int length){
        char arr[4];
        arr[0] = (char)(length & 0x7f);
        arr[1] = (char)((length >> 7)&0x7f);
        arr[2] = (char)((length >> 14)&0x7f);
        arr[3] = (char)((length >> 21)&0x7f);
        std::string Str;
        for(int i = 0; i < 4;i++){
            Str += arr[i];
        }
        return Str;
    }
    void  addClient(std::shared_ptr<eylib::Connection> p);
    void  delClient(std::string str);
    std::shared_ptr<eylib::Connection> findClient(std::string str);
#endif
