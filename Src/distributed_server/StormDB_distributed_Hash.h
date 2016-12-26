/*************************************************************************
	> File Name: StormDB_distributed_Hash.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 14时45分02秒
 ************************************************************************/

#ifndef _STORMDB_DISTRIBUTED_HASH_H
#define _STORMDB_DISTRIBUTED_HASH_H
#include "StormDB_CNode.h"
#include "StormDB_CVirtualNode.h"
#include<map>
class CConHash{
public:
    //构造函数,设置了hash函数
    CConHash()=default;
    CConHash(CHashFun* pFunc);
    void init_Hash_Circle();
    //设置hash函数
    void setFunc(CHashFun* pFunc);
    //添加实体节点 0成功,-1失败. 
    int addNode(CNode* pNode);
    //删除实体节点 0:成功,-1失败.
    int delNode(CNode* pNode);
    //查找实体节点
    CNode* lookupNode(const char* object);
    //获取一致性hash结构的所有虚拟节点数量
    long getVNodes();
private:
    //string是实体服务器的标识名.
    std::map<std::string,CNode> serverNodeList;
    std::map<long,CVirtualNode> virtualNodeList;
}
#endif
