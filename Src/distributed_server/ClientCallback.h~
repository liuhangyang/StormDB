/*************************************************************************
	> File Name: Callback.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 09时22分54秒
 ************************************************************************/

#ifndef _CALLBACK_H
#define _CALLBACK_H
#include <functional>
#include "./Client.h"
#include <memory>
namespace ClientCallback{
    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientconnectionCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>,int)> ClientmessageCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientcloseCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientwriteCompleteCallback;
}
#endif
