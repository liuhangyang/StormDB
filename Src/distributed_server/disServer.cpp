/*************************************************************************
	> File Name: test_Server.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 15时00分36秒
 ************************************************************************/

#include "./disServer.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <map>
using namespace eylib;
void 
messagecallback(std::shared_ptr<eylib::Connection> p,int length){
    char buf[MAXBUF];
    bzero(buf,sizeof(buf));
    p->inputBuffer_.getData(buf,length);
    //printf("buf:%s\n",buf);
    std::string Str("");
    Str +=p->ConnectionName_;
    Str += "\r\n";
    Str += buf;
    Str +="\r\n";
    Str += '\0';
    std::string str = intToByte(Str.size());
    str += Str;
    std::cout << "str================= "<<str <<"str.size----->:"<<str.size()<<  std::endl;
    p->outputBuffer_.append(str);
    int fd = conhash.getFd(buf);
    int sendSize = p->send(fd);
    std::cout <<"sendSize"  <<sendSize <<std::endl;
    if(sendSize < p->outputBuffer_.readableSize()){  //sendSize < 可读的字节,发送缓冲区已满,加入clientName和fd的映射,为注册的写事件做准备.
        senWriteMap[p->ConnectionName_] = fd;
    }
}
void writecallback(std::shared_ptr<eylib::Connection> p){
    int sendSize = p->send(senWriteMap[p->ConnectionName_]);
    if(sendSize == p->outputBuffer_.readableSize()){
        for(auto i= senWriteMap.begin();i!=senWriteMap.end();){
            if(i->first == p->ConnectionName_){
                senWriteMap.erase(i++);
                break;
            }else{
                ++i;
            }
        }
    }
}
void  connectioncallback(std::shared_ptr<eylib::Connection> p){
        std::string str("Client_");
        getClientId(str);
        p->ConnectionName_ = str;
        addClient(p);
}
void  closecallback(std::shared_ptr<eylib::Connection> p){
    std::cout << "客户端: " <<p->ConnectionName_<<" 关闭了!" <<std::endl;
    delClient(p->ConnectionName_);
    close(p->fd_);
}
void Clientmessagecallback1(std::shared_ptr<ClientConnect> p,int m){
        char buf[1024];
        bzero(buf,sizeof(buf));
        p->inputBuffer_.getData(buf,m);
        printf("buf ***************->:%s\n",buf);
        const char *a = getName(buf);
        std::string str(a);
      //  std::cout << "map: " << clientMap[str] <<std::endl;
        std::string Str("");
        getClientData(buf,Str);
        std::cout <<"Str:"<< Str <<std::endl; 
        std::cout << "Str.size() :" <<Str.size() <<std::endl;
        clientMap[str]->outputBuffer_.append(Str);
        clientMap[str]->send(clientMap[str]->fd_);
}
void Clientconnectioncallback1(std::shared_ptr<ClientConnect> p){

}
void Clientclosecallback1(std::shared_ptr<ClientConnect> p){
    std::cout << "数据库服务器: " << p->fd_<<" 关闭了!"<< std::endl;
    close(p->fd_);
}
void Clientwritecallback1(std::shared_ptr<ClientConnect> p){
    
}
void  addClient(std::shared_ptr<eylib::Connection> p){
    clientMap.insert(std::pair<std::string,std::shared_ptr<eylib::Connection>>(p->ConnectionName_,p));
    std::cout << "clientMap[p->ConnectionName_]:" <<p->ConnectionName_<<std::endl;
}
void  delClient(std::string str){
    for(auto i = clientMap.begin();i != clientMap.end();){
        if(i->first == str){
            clientMap.erase(i++);
        }else{
            i++;
        }
    }
}
std::shared_ptr<eylib::Connection> findClient(std::string str){
    if(clientMap.count(str) > 0){
        return clientMap[str];
    }else{
        return NULL;
    }
}
int main(int argc,char *argv[])
{
    uint64_t buf = 1;
    int ret;
    pthread_t tid;
    conhash.setMessageCallback(Clientmessagecallback1);
    conhash.setCloseCallback(Clientclosecallback1);
    conhash.setWriteCompleteCallback(Clientwritecallback1);
    conhash.setConnectionCallback(Clientconnectioncallback1);

    conhash.init_Hash_Circle();
    Server loop(argv[1],atoi(argv[2]),4);
    loop.setMessageCallback(messagecallback);
    loop.setConnectionCallback(connectioncallback);
    loop.setCloseCallback(closecallback);
    loop.start();
   return 0;
}
