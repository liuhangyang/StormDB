/*************************************************************************
	> File Name: StormDB_Error.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 22时36分26秒
 ************************************************************************/

#include<iostream>
#include "StormDB_Error.hpp"
using namespace std;
StormDB_Error::StormDB_Error(const std::string &type,const std::string &err):err_(err){
    cerr << "[ERR][STORMDB]["<< type  << "]" << err <<endl;
}
StormDB_Error::operator std::string(){
    return err_;
}
StormDB_Error::operator const std::string() const{
    return err_;
}
Connection_Error::Connection_Error(const std::string &err):StormDB_Error("connection",err){
    
}
Protocol_Error::Protocol_Error(const std::string &err):StormDB_Error("protocol",err){

}

Key_Error::Key_Error(const std::string &err):StormDB_Error("key",err){
    
}
Value_Error::Value_Error(const std::string &err):StormDB_Error("value",err){

}
