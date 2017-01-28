/*************************************************************************
	> File Name: StormDB_Utils.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 23时03分08秒
 ************************************************************************/

#ifndef _STORMDB_UTILS_H
#define _STORMDB_UTILS_H
#include <vector>
#include <string>
std::string& rtrim(std::string &str,const std::string &ws = " \f\n\r\t\v");
void split(const std::string &str,const std::string &delim,std::vector<std::string> &items);

#endif
