/*************************************************************************
	> File Name: StormDB_Pool.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 14时08分11秒
 ************************************************************************/

#include<iostream>
#include "StormDB_Pool.hpp"
#include <string>
Connection_Pool::Connection_Pool(const std::string &host,int port,int max_connections)
:host(host),port(port),_max_connections(max_connections){

}
Connection_Pool::~Connection_Pool(void){

}
Connection* Connection_Pool::new_connection(void){
    return NULL;
}
void Connection_Pool::disconnect(Connection *conn){
    delete conn;
}
Connection* Connection_Pool:acquire(void){
    Connection *conn = NULL;
    if(_connections_idle.size() > 0){
        conn = _connections_idle.back();
        _connections_idle.pop_back();
    }else{
        conn = new Connection(_host,_port);
    }
    _connections_in_use.insert(conn);
    std::cout << "Acquire_conn:" <<conn->id() <<endl;
    return conn;
}
Connection* Connection_Pool::try_acquire(int timeout){
    return NULL;
}
void Connection_Pool::release(Connection *conn){
    conns_in_use_type::iterator iter = _connections_in_use.find(conn);
    _connections_in_use.erase(iter);
    _connections_idle.push_back(conn);
}
void Connection_Pool::_lock(void){

}
void Connection_Pool::_unlock(void){
    
}
void Connection_Pool::set_max_active(int num){
    _lock();
    _max_connections = num;
    _unlock();
}
void Connection_Pool::set_max_idle(int num){
    _lock();
    _max_idle  = num;
    _unlock();
}
int Connection_Pool::get_max_idle(void) const{
    return _max_idle;
}
int Connection_Pool::get_connections_count(void)const{
    return _max_idle;
}
int Connection_Pool::get_idle_count(void) const{
    return _connections_idle.size();
}
int Connection_Pool::get_in_use_count(void) const{
    return _connections_in_use.size();
}
