/*************************************************************************
	> File Name: StormDB_distributed_Hash.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 14时45分02秒
 ************************************************************************/

#ifndef _STORMDB_DISTRIBUTED_HASH_H
#define _STORMDB_DISTRIBUTED_HASH_H
#define CONFIGFILE "config.conf"
#include "Callback.h"
#include "StormDB_CNode.h"
#include "StormDB_CVirtualNode.h"
#include "StormDB_conf.h"
#include "StormDB_Md5_Hash.h"
#include "StormDB_Md5.h"
#include "StormDB_Epoll.h"
#include <sstream>
#include<map>
#include<memory>
#include <sys/eventfd.h>
#include <thread>
#include <functional>
#include <math.h>
using namespace eylib;
class CConHash{
public:
    //构造函数,设置了hash函数
    CConHash()=default;
    CConHash(std::shared_ptr<CMD5HashFunc> pFunc);
    ~CConHash(){
        workthread->join();
    }
    void init_Hash_Circle();
    //设置hash函数
    void setFunc(std::shared_ptr<CMD5HashFunc> pFunc);
    //添加实体节点 0成功,-1失败. 
    void setEvent_fd(int fd){
        event_fd = fd;
    }
    int addNode(std::shared_ptr<CNode> pNode);
    //删除实体节点 0:成功,-1失败.
    int delNode(std::shared_ptr<CNode> pNode);   //查找实体节点
    CNode* lookupNode(const char* object);
    //初始化添加真实节点.
    void putSerNode(std::shared_ptr<CNode> pNode,std::string Iden);
    //获取一致性hash结构的所有虚拟节点数量
    long getVNodes();
    //添加虚拟节点
    void putVirNode(std::shared_ptr<CVirtualNode> VNode,long hash);
    //int转换为string 
    std::string int_toString(int n);
    int createFd(){
        int fd = eventfd(0,EFD_NONBLOCK);
        assert(fd > 0);
        return fd;
    }
    static void threadFunc(int fd,CConHash *conhash);
    void writeToFd(int fd){
        uint64_t buff = fd;
        printf("event_fd:%d\n",event_fd);
        int ret = write(event_fd,&buff,sizeof(buff));
        assert(ret == sizeof(buff));
    }
    void start();
    int getFd(const std::string str){
        std::hash<std::string> Hash;
        auto one = virtualNodeList.upper_bound(Hash(str)%(long)(pow(2,32)-1));
        if(one == virtualNodeList.end()){
            one = virtualNodeList.begin();
        }
        int fd = one->second->getNode()->getSockfd();
        return fd;
    }
    void setConnectionCallback(ClientconnectionCallback cb){
        clientconnectionCallback_ = cb;
    }
    void setMessageCallback(ClientmessageCallback cb){
        clientmessageCallback_ = cb;
    }
    void setCloseCallback(ClientcloseCallback cb){
        clientcloseCallback_ = cb;
    }
    void setWriteCompleteCallback(ClientwriteCompleteCallback cb){
        clientwriteCompleteCallback_ = cb;
    }
    ClientmessageCallback getMessageCallback(void){
        return clientmessageCallback_;
    }
    ClientcloseCallback getCloseCallback(void){
        return clientcloseCallback_;
    }
    ClientwriteCompleteCallback getWriteCompleteCallback(void){
        return clientwriteCompleteCallback_;
    }
    ClientconnectionCallback getConnectionCallback(void){
        return clientconnectionCallback_;
    }
private:
    //string是实体服务器的标识名.
    int event_fd;
    std::map<std::string,std::shared_ptr<CNode>> serverNodeList;
    std::map<long,std::shared_ptr<CVirtualNode>> virtualNodeList;
    std::shared_ptr<CMD5HashFunc> func;
    std::shared_ptr<std::thread> workthread;
    ClientmessageCallback clientmessageCallback_;
    ClientcloseCallback clientcloseCallback_;
    ClientconnectionCallback clientconnectionCallback_;
    ClientwriteCompleteCallback clientwriteCompleteCallback_;
};
#endif
