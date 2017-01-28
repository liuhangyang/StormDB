/*************************************************************************
	> File Name: Callback.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月07日 星期六 09时22分54秒
 ************************************************************************/

#ifndef _CALLBACK_H
#define _CALLBACK_H
#include "Connection.h"
#include "Client.h"
#include <memory>
namespace eylib{
    typedef std::function<void(std::shared_ptr<Connection>)> connectionCallback;
    typedef std::function<void(std::shared_ptr<Connection>,int)> messageCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> closeCallback;
    typedef std::function<void(std::shared_ptr<Connection>)> writeCompleteCallback;

    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientconnectionCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>,int)> ClientmessageCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientcloseCallback;
    typedef std::function<void(std::shared_ptr<ClientConnect>)> ClientwriteCompleteCallback;
}
#endif
