/*************************************************************************
	> File Name: StormDB_Hash.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 19时00分08秒
 ************************************************************************/

#ifndef _STORMDB_HASH_H
#define _STORMDB_HASH_H
//定义Hash函数接口,用于计算节点的hash值
class HashFunc{
public:
    virtual long getHashVal(const char *,int)=0;
};
#endif
