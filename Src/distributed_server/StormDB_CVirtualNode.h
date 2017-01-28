/*************************************************************************
	> File Name: StormDB_CVirtualNode.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 18时35分15秒
 ************************************************************************/

#ifndef _STORMDB_CVIRTUALNODE_H
#define _STORMDB_CVIRTUALNODE_H
#include "StormDB_CNode.h"
#include<memory>
//虚拟节点
class CVirtualNode{
public:
    //构造函数
    CVirtualNode()=default;
    CVirtualNode(std::shared_ptr<CNode> pNode);
    //设置虚拟节点指向的实体节点
    void setNode(std::shared_ptr<CNode> pNode);
    //获取虚拟节点所指向的实体节点
    std::shared_ptr<CNode> getNode();
    //设置虚拟节点的hash值
    void setHash(long pHash);
    //获取虚拟节点的hash值
    long getHash();
private:
    long hash; //hash值
    //CNode *node; //虚拟节点所指向的实体节点.
    std::shared_ptr<CNode> node; //虚拟节点指向实体节点.  
};
#endif
