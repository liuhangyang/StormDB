/*************************************************************************
	> File Name: StormDB_Md5_Hash.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 19时12分16秒
 ************************************************************************/

#ifndef _STORMDB_MD5_HASH_H
#define _STORMDB_MD5_HASH_H
class CMD5HashFunc{
public:
    CMD5HashFunc()=default; 
    long  getHashVal(const char *str,int nTime);
    
};
#endif
