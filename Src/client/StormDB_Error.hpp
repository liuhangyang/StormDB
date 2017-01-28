/*************************************************************************
	> File Name: StormDB_Error.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 22时28分07秒
 ************************************************************************/

#ifndef _STORMDB_ERROR_H
#define _STORMDB_ERROR_H
#include <string>
class StormDB_Error{
public:
    StormDB_Error(const std::string &type,const std::string &err);
    operator std::string();
    operator const std::string()const;
private:
    std::string err_;
};
class Connection_Error : public StormDB_Error{
public:
    Connection_Error(const std::string &err);
};
class Protocol_Error : public StormDB_Error{
public:
    Protocol_Error(const std::string &err);
};
class Key_Error : public StormDB_Error{
public:
    Key_Error(const std::string &err);
};
class Value_Error : public StormDB_Error{
public:
    Value_Error(const std::string &err);
};
#endif

