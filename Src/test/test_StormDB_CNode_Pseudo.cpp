/*************************************************************************
	> File Name: test_StormDB_CNode_Pseudo.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月26日 星期一 20时58分40秒
 ************************************************************************/

#include<iostream>
#include "../distributed_server/StormDB_CNode.h" 
int main(int argc,char *argv[])
{
     CNode node("client1",5,"127.0.0.1",8888);
    node.do_connect();
    std::string str("yanglon  gfei");
    node.do_write(str);
    char buf[1024];
    memset(buf,0,sizeof(buf));    
    node.do_read(buf);
    std::cout << "buf:"<<buf<<std::endl;
   return 0;
}
