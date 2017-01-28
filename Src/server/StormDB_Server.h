/*************************************************************************
	> File Name: StormDB_Server.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月25日 星期三 20时34分12秒
 ************************************************************************/

#ifndef _STORMDB_SERVER_H
#define _STORMDB_SERVER_H
#include <iostream>
#include "StormDB_DB.h"
#include "StormDB_String.h"
#include "./StormDB_DBAll.h"
#include "./StormDB_KV.h"
#include "./StormDB_Callback.h"
#include <memory>
#include  "./StormDB_Epoll.h"
class StormDBServer{
public:
    StormDBServer(){
        serverepoll = std::shared_ptr<ServerEpoll>(new ServerEpoll());
        DB = std::shared_ptr<StormDBAll> (new StormDBAll(16,4,4));
    }
    ~StormDBServer(){
        
    }
    void Start();
    void setServerConnectCallback(ServerConnectCallback cb){
        serverConnectCallback_ = cb;
    }
    void setServerMessageCallback(ServerMessageCallback cb){
        serverMessageCallback_ = cb;
    }
    void setServerCloseCallback(ServerCloseCallback cb){
        serverCloseCallback_ = cb;
    }
    void setServerWriteCallback(ServerWriteCallback cb){
        serverWriteCallback_ = cb;
    }
    ServerConnectCallback getServerConnectCallback(){
        return serverConnectCallback_;
    }
    ServerMessageCallback getServerMessageCallback(){
        return serverMessageCallback_;
    }
    ServerCloseCallback getServerCloseCallback(){
        return serverCloseCallback_;
    }
    ServerWriteCallback getServerWriteCallback(){
        return serverWriteCallback_;
    }
    std::shared_ptr<StormDBAll> returnDB(){
        return DB;
    }
private:

    ServerConnectCallback serverConnectCallback_;
    ServerMessageCallback serverMessageCallback_;
    ServerCloseCallback  serverCloseCallback_;
    ServerWriteCallback  serverWriteCallback_;
    std::shared_ptr<ServerEpoll>  serverepoll;
    std::shared_ptr<StormDBAll> DB;
};
#endif
