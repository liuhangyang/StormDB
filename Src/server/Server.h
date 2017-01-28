/*************************************************************************
	> File Name: Server.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月26日 星期四 10时20分25秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include <memory>
#include "./StormDB_Server.h"
#include "./StormDB_Connect.h"
#include "./StormDB_Utils.hpp"
#include "./ThreadPool.hpp"
#include "./StormDB_Task.h"
std::shared_ptr<StormDBServer> server(new StormDBServer());
ThreadPool pool(1);
void serverMessage(std::shared_ptr<ServerConnect> p,int m);
void serverConnect(std::shared_ptr<ServerConnect> p);
void serverClose(std::shared_ptr<ServerConnect> p);
void serverWrite(std::shared_ptr<ServerConnect> p);
#endif
