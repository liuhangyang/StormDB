/*************************************************************************
	> File Name: StormDB_CNode.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 15时59分30秒
 ************************************************************************/

#ifndef _STORMDB_CNODE_H
#define _STORMDB_CNODE_H
//实体节点
#include <string.h>
#include<iostream>
class CNode{
public:
    //构造函数
    CNode()=default;
    CNode(const char *pIden,int pVNodeCount,const void* pData,int p);
    //获取节点标识
    std::string getIden() const;
    //获取实体节点的虚拟节点数量
    int getVNodeCount();
    //设置实体节点数据值
    void setData(const void *data);
    //获取实体节点的数据值
    const void *getData()const;
    void setSockfd(int fd);
    int getSockfd();
private:
    void setCNode(const char *pIden,int pVNodeCount,const void* pData,int p);
     std::string Iden; //节点标识串
    int vNodeCount; //虚拟节点数目
    const void* data; //真实节点的ip.
    int port; //真实节点的端口
    int sockfd; //连接的sockfd值.
};
#endif
