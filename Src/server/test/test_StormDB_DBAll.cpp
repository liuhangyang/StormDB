/*************************************************************************
	> File Name: test_StormDB_DBAll.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月19日 星期四 20时15分18秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_DB.h"
#include "../StormDB_String.h"
#include "../StormDB_KV.h"
#include "../StormDB_DBAll.h"
#include <vector>
#include <string>
#include <unistd.h>
void fun3(){
    StormDBAll db(16,4,4);
    char *a;
  /* a = db.handle("SET","yang","123","\0");
    std::cout << a <<std::endl;
    a= db.handle("APPEND","yang","45687890","\0");
    std::cout << a <<std::endl;
    a = db.handle("GET","yang","\0","\0");
    std::cout << a <<std::endl;
    a = db.handle("DEL","yang","\0","\0");
    std::cout << a <<std::endl;
    a= db.handle("APPEND","yang","ddd","\0");
    std::cout << a <<std::endl;
    a = db.handle("GET","yang","\0","\0");
    std::cout << a << std::endl;*/

    a = db.handle("HSET","book","name","jianai");
    std::cout << a << std::endl;
    a = db.handle("HSET","book","price","23");
    std::cout << a << std::endl;
    a = db.handle("HGETALL","book","\0","\0");
    std::cout << a <<std::endl;
    a = db.handle("HDEL","book","price","\0");
    std::cout << a <<std::endl;
    a = db.handle("HGETALL","book","\0","\0");
    std::cout << a <<std::endl;

/*
    a = db.handle("LSET", "yang","longfei","\0");
    std::cout << a <<std::endl;
    a= db.handle("LGET","yang","\0","\0");
    std::cout << a <<std::endl;
    a = db.handle("LPUSH","tian","s","\0");
    std::cout << a <<std::endl;
    a = db.handle("LPUSH","tian","f","\0");
    std::cout << a <<std::endl;
    a = db.handle("LPOP","tian","\0","\0");
    std::cout << a <<std::endl;

    a = db.handle("RPUSH","tis","ccd","\0");
    std::cout << a <<std::endl;
    
    a= db.handle("RPOP","tis","\0","\0");*/
}
int main(int argc,char *argv[])
{
    fun3();

   return 0;
}
