//
// Created by yang on 16-8-4.
//

#ifndef TSHH_THREADPOOL_HPP
#define TSHH_THREADPOOL_HPP

#include <list>
#include<stdio.h>
#include<string.h>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <sys/types.h>
#include<sys/socket.h>
#include<vector>
#include "SyncQueue.hpp"
#include "./StormDB_Task.h"
const int MaxTaskCount=100;
class ThreadPool {
public:
    ThreadPool(int numThreads=std::thread::hardware_concurrency()):m_queue(MaxTaskCount){
        Start(numThreads);
    }
    ~ThreadPool(void){
        //如果没有停止则主动停止线程池
        Stop();
    }
    void Stop(){
        //保证多线程情况下只调用一次StopThreadGroup
        std::call_once(m_flag,[this]{StopThreadGroup();});
    }
    void AddTask(Task&& task){
        m_queue.Put(std::forward<Task>(task));
    }
    void AddTask(const Task & task){
        m_queue.Put(task);
    }

    void Start(int numThreads){
        m_running=true;
        //创建线程组
        for(int i=0;i<numThreads;++i){
            m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread,this));
        }
    }
   void work(Task &task){
	Task mytask;
	mytask.do_task(task);
   }

private:
    void RunInThread(){
        while(m_running){
            //取任务分别执行
            std::list<Task> list;
            m_queue.Take(list);
            for(auto& task:list){
                if(!m_running){
                    return;
                }
               	work(task);
            }

        }
    }
    void StopThreadGroup() {
        m_queue.Stop();
        m_running=false;    //置为flase,让内部线程跳出循环并退出.

        for(auto thread : m_threadgroup){
            if(thread){
                thread->join();
            }
        }
        m_threadgroup.clear();
    }
    std::list<std::shared_ptr<std::thread>> m_threadgroup;   //处理任务的线程组.
    SyncQueue<Task> m_queue;      //同步队列
    std::atomic_bool m_running;          //是否停止的标志.
    std::once_flag m_flag;
};
#endif //TSHH_THREADPOOL_HPP
