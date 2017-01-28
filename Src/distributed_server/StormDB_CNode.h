/*************************************************************************
	> File Name: StormDB_CNode.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 15时59分30秒
 ************************************************************************/

#ifndef _STORMDB_CNODE_H
#define _STORMDB_CNODE_H
//实体节点
//c++11
#include <string.h>
#include<iostream>

//net
#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
class CNode{
public:
    //构造函数
    CNode()=default;
    CNode(const char *pIden,int pVNodeCount,const char* pData,int& p);
    //获取节点标识
    std::string getIden() const;
    //获取实体节点的虚拟节点数量
    int getVNodeCount();
    //设置实体节点数据值
    void setData(const char *data);    //获取实体节点的数据值
     const char *getData()const;
    void setSockfd(int fd);
    int getSockfd();
    
    int do_connect();
    int do_read(char *str);
    int do_write(std::string& str);  
private:
    void setCNode(const char *pIden,int pVNodeCount,const char* pData,int p);
    std::string Iden; //节点标识串
    int vNodeCount; //虚拟节点数目
    const char* data; //真实节点的ip.
    int port; //真实节点的端口
    int connfd; //连接的sockfd值.
};
#endif
