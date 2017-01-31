/*************************************************************************
	> File Name: Callback.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 09时22分54秒
 ************************************************************************/

#ifndef _CALLBACK_H
#define _CALLBACK_H
#include <functional>
#include "Connection.h"
#include <memory>
namespace eylib{
    typedef std::function<void(void)> connectionCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> messageCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> closeCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> writeCompleteCallback;
}
#endif
