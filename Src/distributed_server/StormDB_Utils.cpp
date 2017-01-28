/*************************************************************************
	> File Name: StormDB_Utils.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 23时06分32秒
 ************************************************************************/

#include<iostream>
#include "./StormDB_Utils.hpp"
#include <sstream>
#include <cassert>
#include <cerrno>
using namespace std;
std::string& rtrim(std::string &str,const std::string &ws){
    std::string::size_type pos = str.find_last_not_of(ws);
    str.erase(pos+1);
    return str;
}
void split(const std::string &str,const std::string &delim,std::vector<std::string> &items){
    std::string::size_type pos_old = 0,pos_new = 0;
    std::string::size_type size_delim = delim.length();

    while(1){
        pos_new = str.find(delim,pos_old);
        if(pos_new != std::string::npos){
            items.push_back(str.substr(pos_old,pos_new-pos_old));
            pos_old = pos_new + size_delim;
        }else if(pos_old <= str.size()){
            items.push_back(str.substr(pos_old));
            break;
        }else{
            break;
        }
    }
}
