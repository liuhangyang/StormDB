/*************************************************************************
	> File Name: StormDB_Ziplist.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 14时27分41秒
 ************************************************************************/

#ifndef _STORMDB_ZIPLIST_H
#define _STORMDB_ZIPLIST_H
#include <iostream>
#include <vector>
template <typename T>
class Ziplist{
private:
    std::vector<T> data; //vector 容器列表.
public:
    Ziplist(){}
    Ziplist(std::vector<T> rhs); //用另一个vector容器初始化.
    ~Ziplist(){}
    void Ziplist_add(T rhs); //添加一个节点
    void Ziplist_del(T rhs);//删除一个节点.
    bool Ziplist_del_more(T first,T last); //删除指定的连续的节点.
    int Ziplist_size();//返回列表目前的节点数量.
    int Ziplist_size_bytes();//返回列表目前占用内存字节数.
    bool Ziplist_find(T rhs); //查找链表内是否由指定值的节点.

    void Ziplist_show(); //测试函数,用来打印列表的信息.
    std::vector<T> Ziplist_return();
    void Ziplist_destory();
    
};
template <typename T>
Ziplist<T>::Ziplist(std::vector<T> rhs){
    data = rhs;
}
template <typename T>
void Ziplist<T>::Ziplist_add(T rhs){
    data.push_back(rhs);
}
template  <typename T>
void Ziplist<T>::Ziplist_del(T rhs){
    for(auto item = data.begin();item != data.end();){
        if(*item == rhs){
            item = data.erase(item);
        }else{
            item++;
        }
    }
}
template <typename T>
bool Ziplist<T>::Ziplist_del_more(T first,T last){
    for(auto item = data.begin(); item != data.end(); ++item){
        if(*item == first){
            for(auto iterr = item;iterr != data.end();iterr++){
                if(*iterr == last){
                    data.erase(item,++iterr);
                    return true;
                }
            }
            return false;
        }
    }
}
template <typename T>
int Ziplist<T>::Ziplist_size(){
    return data.size();
}
template <typename T>
int Ziplist<T>::Ziplist_size_bytes(){
    return (data.size() * sizeof(T));
}
template <typename T>
bool Ziplist<T>::Ziplist_find(T rhs){
    for(auto item : data){
        if(item == rhs){
            return true;
        }
    }
    return false;
}
template <typename T>
void Ziplist<T>::Ziplist_show(){
    for(auto item:data){
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
template <typename T>
std::vector<T> Ziplist<T>::Ziplist_return(){
    return data;

}
template <typename T>
void Ziplist<T>::Ziplist_destory(){
    std::vector<T>().swap(data);
}
#endif
