/*************************************************************************
	> File Name: StormDB_Pool.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月20日 星期五 22时45分50秒
 ************************************************************************/

#ifndef _STORMDB_POOL_H
#define _STORMDB_POOL_H
#include <set>
#include <vector>
#include "StormDB_Connection.hpp"
class Connection_Pool{
    typedef std::vector<Connection*> conns_idle_type;
    typedef std::set<Connection*>  conns_in_use_type;
    Connection_Pool(const std::string &host = "127.0.0.1",
                    int port = 6379,int max_connections = 32);
    ~Connection_Pool(void);

    Connection* acquire(void);
    Connection& try_acquire(int timeout = 0);
    void release(Connection *conn);

    void set_max_active(int num);
    void set_max_idle(int num);
    int get_max_connections(void) const;
    int get_max_idle(void) const;
    int get_connections_count(void) const;
    int get_idle_count(void) const;
    int get_in_use_count(void) const;
private:
    Connection_Pool(const Connection_Pool &);
    Connection_Pool& operator=(const Connection_Pool &);

    Connection* new_connection(void);
    void disconnection(Connection *conn);

    void _lock(void);
    void _unlock(void);
    bool _wait(int timeout);
    void _raise(void);
private:
    std::string _host;
    int _port;
    int _max_connections;
    int _max_idle;

    conns_idle_type  _connections_idle;
    conns_in_use_type _connections_in_use;

};

#endif
