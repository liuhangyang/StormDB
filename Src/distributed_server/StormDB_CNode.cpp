/*************************************************************************
	> File Name: StormDB_CNode.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 18时31分15秒
 ************************************************************************/
#include"StormDB_CNode.h"
#include<iostream>
#include<string.h>
#include <fcntl.h>

CNode::CNode(const char *pIden,const int pVNodeCount,const char* pData,int& p){
    setCNode(pIden,pVNodeCount,pData,p);

}
void
CNode::setCNode(const char *pIden,const int pVNodeCount,const char* pData,int p){
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
CNode::setData(const char *pData){
    this->data = pData;
}
const char*
CNode::getData()const{
    return this->data;
}
void 
CNode::setSockfd(int fd){
    this->connfd = fd;
}
int 
CNode::getSockfd(){
    return connfd;
}
int 
CNode::do_connect(){
    struct sockaddr_in server_listen_addr;
    int server_fd;
    bzero(&server_listen_addr,sizeof(server_listen_addr));
    server_listen_addr.sin_family = AF_INET;
    server_listen_addr.sin_port = htons(this->port);
    inet_pton(AF_INET,(char *)data,&server_listen_addr.sin_addr);
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    int ret = connect(server_fd,(struct sockaddr*)&server_listen_addr,sizeof(struct sockaddr_in));
    if(ret < 0){
        perror("error:socket connect!");
        return -1;
    }
    setSockfd(server_fd);
    std::cout << "server_fd: "<<server_fd<<std::endl;
    return ret;
}
/*int 
CNode::do_write(std::string& str){
    int length = str.length();
    const char *buf = str.c_str();
    
    int use = write(connfd,buf,length);
    int use_less = length  - use;
    if(use < 0){
        close(connfd);
        return -1;
    }
    return use_less;
}
int CNode::do_read(char *str){
    int length = read(connfd,str,1024);
    if(length < 0){
        close(connfd);
        return -1;
    }
    return length;
}*/
/*
int main(){
    CNode node("client1",5,"127.0.0.1",8888);
    node.do_connect();
    std::string str("yanglongfei");
    node.do_write(str);
    char buf[1024];
    memset(buf,0,sizeof(buf));    
    node.do_read(buf);
    std::cout << "buf:"<<buf<<std::endl;
}*/
