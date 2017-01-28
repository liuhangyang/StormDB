/*************************************************************************
	> File Name: StormDB_Callback.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月25日 星期三 20时38分40秒
 ************************************************************************/

#ifndef _STORMDB_CALLBACK_H
#define _STORMDB_CALLBACK_H
#include "StormDB_Connect.h"
#include <memory>
typedef std::function<void(std::shared_ptr<ServerConnect>)> ServerConnectCallback;
typedef std::function<void(std::shared_ptr<ServerConnect>,int)> ServerMessageCallback;
typedef std::function<void(std::shared_ptr<ServerConnect>)> ServerCloseCallback;
typedef std::function<void(std::shared_ptr<ServerConnect>)> ServerWriteCallback;
#endif
