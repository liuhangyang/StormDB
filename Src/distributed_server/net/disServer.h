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
#include "Server.h"
using namespace eylib;
int clientId = 0;
    std::map<std::string,std::shared_ptr<eylib::Connection>> clientMap;
    void messagecallback(std::shared_ptr<eylib::Connection> p);
    void connectioncallback(std::shared_ptr<eylib::Connection> p);
    void closecallback(std::shared_ptr<eylib::Connection> p);
    void getClientId(std::string& str){
        std::stringstream ss;
        ss << clientId;
        std::string s;
        ss >> s;
        str += s;
        clientId ++;
    }
    void  addClient(std::shared_ptr<eylib::Connection> p);
    void  delClient(std::string str);
    std::shared_ptr<eylib::Connection> findClient(std::string str);
#endif
