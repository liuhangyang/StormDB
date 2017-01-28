/*************************************************************************
	> File Name: StormDB_Command.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 22时15分10秒
 ************************************************************************/

#ifndef STORMDB_COMMAND
#define STORMDB_COMMAND
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <endian.h>
#include <stdio.h>
#include <stdint.h>
using namespace std;
class Command{
public:
    const static std::string CRLF;
    explicit Command() = default;
    template <typename T>
    Command& operator << (T const& datum){
        _buffer << ' '<<datum;
        return *this;
    }
    template <typename T>
    Command& operator << (const vector<T> &data){
        size_t n = data.size();   
        _buffer <<"*"<<n;
        for(size_t i = 0; i < n;++i)
        {
            _buffer << CRLF;
            _buffer << "$";
            _buffer << data[i].size();
            _buffer << CRLF;
            _buffer << data[i];
        }
        return *this;
    }
    const std::string getbuffer(void){
        _buffer << CRLF;
        return _buffer.str();
    }
private:
    ostringstream _buffer;
};
#endif 
