/*************************************************************************
	> File Name: mutex.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 17时11分22秒
 ************************************************************************/

#ifndef _MUTEX_H
#define _MUTEX_H
#include <thread>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
namespace eylib
{
    class Mutex
    {
    public:
        Mutex(){
            pthread_mutex_init(&mutex_,NULL);
        }
        ~Mutex(){
            pthread_mutex_destroy(&mutex_);
        }
        void lock() //上锁
        {
            int ret = pthread_mutex_lock(&mutex_);
            printf("yang = %p\n",&Mutex_);
            assert(ret == 0);
        }
        void unlock(){ //解锁
            int ret = pthread_mutex_unlock(&mutex_);
            assert(ret == 0);
        }
        pthread_mutex_t *getMutex(){ //获得互斥锁.
            return &mutex_;
        }
    private:
        pthread_mutex_t mutex_;
    };
}
#endif
