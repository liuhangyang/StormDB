/*************************************************************************
	> File Name: StormDB_CNode.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 18时31分15秒
 ************************************************************************/
#include"StormDB_CNode.h"
#include<iostream>
#include<string.h>
CNode::CNode(const char *pIden,const int pVNodeCount,const void* pData,int p){
    setCNode(pIden,pVNodeCount,pData,p);

}
void
CNode::setCNode(const char *pIden,const int pVNodeCount,const void* pData,int p){
    std::string str(pIden);
    Iden=str;
    vNodeCount = pVNodeCount;
    data = pData;
    this->port = p;
}
std::string 
CNode::getIden()const{
    return Iden;
}
int
CNode::getVNodeCount(){
    return vNodeCount;
}
void
CNode::setData(const void *pData){
    this->data = pData;
}
const void*
CNode::getData()const{
    return this->data;
}
void 
CNode::setSockfd(int fd){
    this->sockfd = fd;
}
int 
CNode::getSockfd(){
    return sockfd;
}
int main(){

}
