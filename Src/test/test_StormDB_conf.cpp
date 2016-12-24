/*************************************************************************
	> File Name: test_FDB_conf.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 13时20分18秒
 ************************************************************************/

#include<iostream>
#include"../server/StormDB_conf.h"
int main()  
{  
    int port;  
    std::string ipAddress;  
    std::string username;  
    std::string password;  
    const char ConfigFile[]= "config.conf";   
    Config configSettings(ConfigFile);  
      
    port = configSettings.Read("port",0);  
    ipAddress = configSettings.Read("ipAddress", ipAddress);  
    username = configSettings.Read("username", username);  
    password = configSettings.Read("password", password);  
    std::cout<<"port:"<<port<<std::endl;  
    std::cout<<"ipAddress:"<<ipAddress<<std::endl;  
    std::cout<<"username:"<<username<<std::endl;  
    std::cout<<"password:"<<password<<std::endl;  
    //configSettings.Add("type","false");
   // std::ofstream out("config.conf");
   // out << configSettings;
    return 0;  
}  


