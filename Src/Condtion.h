/*************************************************************************
	> File Name: Condtion.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 18时04分37秒
 ************************************************************************/

#ifndef _CONDTION_H
#define _CONDTION_H
#include <thread>
#include <assert>
#include <stdio.h>
#include <pthread.h>
namespace eylib{
    class Condtion{
    public:
        Condtion(pthread_mutex_t *mutex):mutex_(mutex){
            pthread_cond_init(&cond_,NULL);
        }
        ~Condtion(){
            pthread_cond_destroy(&cond_);
        }
        void wait(){
            int ret = pthread_cond_wait(&cond_,mutex_);
            assert(ret == 0);
        }
        void notify(){
            int ret = pthread_cond_signal(&cond_);
            assert(ret == 0);
        }
        void notifyAll(){
            int ret = pthread_cond_broadcast(&cond_);
            assert(ret == 0);
        }
    private:
        pthread_mutex_t *mutex_;
        pthread_cond_t cond_;
    };
}
#endif
