/*************************************************************************
	> File Name: StormDB_Task.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月26日 星期四 13时03分09秒
 ************************************************************************/

#ifndef _STORMDB_TASK_H
#define _STORMDB_TASK_H
#include <memory>
#include "./StormDB_DBAll.h"
#include "./StormDB_Connect.h"
#include <stdlib.h>
class Task{
public:
    Task(std::shared_ptr<ServerConnect> p,std::shared_ptr<StormDBAll> s,int m){
       // strcpy(buf,m);
        server = s;
        length = m;
        conn = p;
    }
    Task() = default;
    ~Task()= default;
    void do_task(Task &task);
std::shared_ptr<StormDBAll> server; 
//char buf[1024];
std::shared_ptr<ServerConnect> conn;
    int length;
};
#endif
