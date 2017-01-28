/*************************************************************************
	> File Name: StormDB_distributed_Hash.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月26日 星期一 11时42分15秒
 ************************************************************************/
#include "StormDB_distributed_Hash.h"
#include<iostream>
#include<stdio.h>
#include<memory>
#include<map>
#include<math.h>
//构造函数
CConHash::CConHash(std::shared_ptr<CMD5HashFunc> pFunc){
    this->func = pFunc;

}
//设置Hash函数
void
CConHash::setFunc(std::shared_ptr<CMD5HashFunc> pFunc){
    this->func = pFunc;
}
void
CConHash::putSerNode(std::shared_ptr<CNode> pNode,std::string Iden){
    serverNodeList[Iden] = pNode;
}
void
CConHash::putVirNode(std::shared_ptr<CVirtualNode> VNode,long hash){
    virtualNodeList[hash] = VNode;
}
std::string
CConHash::int_toString(int n){
    std::ostringstream stream;
    stream << n;
    return stream.str();
}
std::string getMd5Value(std::string& str){
    MD5 md5 = MD5(str);
    return md5.hexdigest();
}
void
CConHash::init_Hash_Circle(){
          start();
        //设置Hash函数.
        if(func == NULL){
            std::shared_ptr<CMD5HashFunc> pFunc(new CMD5HashFunc());
            func = pFunc;
        }
        //读取配置文件
            Config configSettings(CONFIGFILE);
            int serverNum = configSettings.Read("server_num",0);
            int virNodeNum;
            int port;
            std::string data_ip;
        for(int i = 0;i < serverNum; ++i){
            std::string No_i = int_toString(i);
            //获取配置文件中的主机地址,虚拟节点个数,以及端口号.
            std::string raw_server_ip("server_");
            std::string raw_virtualNodeNum("virtual_node_num_server_");
            std::string raw_server_port("port_");
            //标识真实节点
            std::string raw_server_Iden("Mechine_");
            //标识虚拟节点.
            std::string raw_virtualNode_Iden("virNodeNum_");
            
            raw_server_ip.append(No_i);
            raw_virtualNodeNum.append(No_i);
            raw_server_port.append(No_i);
            raw_server_Iden.append(No_i);
            //读配置及文件.
            virNodeNum = configSettings.Read(raw_virtualNodeNum,0);
            port = configSettings.Read(raw_server_port,0);
            data_ip = configSettings.Read(raw_server_ip,data_ip);
            //std::cout << "data_ip: "<<data_ip<<std::endl;
            //构造虚拟节点的标识.
            raw_virtualNode_Iden.append(data_ip);
            raw_virtualNode_Iden.append("_");
            std::string Iport = int_toString(port);
            raw_virtualNode_Iden.append(Iport);
            //std::cout << "ip:"<<data_ip<<" port:"<<port<<std::endl;
            std::shared_ptr<CNode> node(new CNode(raw_server_Iden.c_str(),virNodeNum,data_ip.c_str(),port));
            //printf("地址:%ld\n",node->getData());
           // std::cout << "use_count:"<<node.use_count()<<std::endl;
            //创建一条连接.
            node->do_connect();
            printf("连接了一次");
            writeToFd(node->getSockfd());
            putSerNode(node,raw_server_Iden);
            for(int j = 0;j < virNodeNum/4;++j){
                std::string VNo_j = int_toString(j);
                std::string virNode_Iden(raw_virtualNode_Iden);
                virNode_Iden.append(VNo_j);
                const std::string md5Value = getMd5Value(virNode_Iden);
                for(int h = 0; h < 4;h++){
                    long hash_value = func->getHashVal(md5Value.c_str(),h);
                    std::shared_ptr<CVirtualNode> cvNode(new CVirtualNode(node));
                    putVirNode(cvNode,hash_value);
                }
            }
        }

   /*for(auto t:serverNodeList){
        std::cout << "标识:"<<t.first << " ip:"<<t.second->getData()<<std::endl;
    }
    for(auto t:virtualNodeList){
        std::cout << "Hash_value: "<<t.first << t.second->getNode()->getData() << "sockfd: "<<t.second->getNode()->getSockfd()<< std::endl;
    }*/
      /*  std::hash<std::string> Hash;     
        std::string str("yanglodei");
        std::cout << "key_Hash:"<<(Hash(str)%(long)(pow(2,32)-1))<<std::endl;
        auto one = virtualNodeList.upper_bound(Hash(str)%(long)(pow(2,32)-1));
        if(one == virtualNodeList.end()){
            std::cout << "not found--------------------------->"<<std::endl;
            one = virtualNodeList.begin();
        }   
        std::cout <<"one.hash"<<one->first << "one.sockfd"<<one->second->getNode()->getSockfd()<<std::endl;
        one->second->getNode()->do_write(str);


        std::string str1("waihao00000");
        std::cout << "key_Hash:"<<(Hash(str1)%(long)(pow(2,32)-1))<<std::endl;
        auto one1 = virtualNodeList.upper_bound(Hash(str1)%(long)(pow(2,32)-1));
        if(one1 == virtualNodeList.end()){
            std::cout << "not found"<<std::endl;
            one1 = virtualNodeList.begin();
        }   
        std::cout <<"one1.hash"<<one1->first << "one1.sockfd"<<one1->second->getNode()->getSockfd()<<std::endl;
        one1->second->getNode()->do_write(str1);
        
    
        std::string str2("hddddduxxxxxing");
        std::cout << "key_Hash:"<<(Hash(str2)%(long)(pow(2,32)-1))<<std::endl;
        auto one2 = virtualNodeList.upper_bound(Hash(str2)%(long)(pow(2,32)-1));
        if(one2 == virtualNodeList.end()){
            std::cout << "not found"<<std::endl;
            one2 = virtualNodeList.begin();
        }   
        std::cout <<"one2.hash"<<one2->first << "one2.sockfd"<<one2->second->getNode()->getSockfd()<<std::endl;
        one2->second->getNode()->do_write(str2);*/
}

//添加节点 成功0,失败-1;
int
CConHash::addNode(std::shared_ptr<CNode> pNode){
    
}
//删除节点 成功0,失败-1;
int 
CConHash::delNode(std::shared_ptr<CNode>pNode){
    
}
//查找实体节点
void 
CConHash::start(){
    int fd = createFd();
    setEvent_fd(fd);
    workthread = std::make_shared<std::thread>(threadFunc,fd,this);
}
void 
CConHash::threadFunc(int fd,CConHash *conhash){
    ClientEpoll epoll(fd);
    epoll.setMessageCallback(conhash->getMessageCallback()); //
    epoll.setCloseCallback(conhash->getCloseCallback());
    epoll.setWriteCompleteCallback(conhash->getWriteCompleteCallback());
    epoll.setConnectionCallback(conhash->getConnectionCallback());
    epoll.loop();
}
/*
int main(int argc,char *argv[])
{
    
    std::shared_ptr<CMD5HashFunc> pFunc(new CMD5HashFunc());
    CConHash conhash(pFunc);
    conhash.init_Hash_Circle();
   return 0;
}*/
