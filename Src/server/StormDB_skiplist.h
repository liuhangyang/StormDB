/*************************************************************************
	> File Name: StormDB_skiplist.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月21日 星期三 18时10分13秒
 ************************************************************************/

#ifndef _STORMDB_SKIPLIST_H
#define _STORMDB_SKIPLIST_H
#include <iostream>
#include <stdlib.h>
#include <math.h>

template<class E>
class SkipNode{
public:
    //构造函数
    //size 是根据节点的个数计算的最合适的层数.
    SkipNode(int size){
        forward = new SkipNode<E>*[size];
    }
    friend int operator < (SkipNode<E> t1,SkipNode<E> t2){
        if(t1.data < t2.data){
            return 1;
        }else{
            return 0;
        }
    }
    friend int operator > (SkipNode<E> t1,SkipNode<E> t2){
        if(t1.data > t2.data){
            return 1;
        }else{
            return 0;
        }
    }
    friend int operator == (SkipNode<E> t1,SkipNode<E> t2){
        if(t1.data == t2.data){
            return 1;
        }else{
            return 0;
        }
    }
    //成员函数
    void setData(E pData){
        data = pData;
    }
    ~SkipNode(){
        delete[] forward;
    }
    E getData(){
        return data;
    }

    //指针数组
    SkipNode<E> **forward;
private:
    E data;
};
template<class E>
class list_skip{
public:
    list_skip(E large,int MaxE = 10000,float p = 0.5); //构造函数
    list_skip()=default;
    ~list_skip();
    
    int Rlevel();
    int Insert(E Pvalue); //插入元素
    bool Delete(E Pvalue); //删除元素

    E Search(E Pvalue);  //查找指定的值

    void print();
private:
    int maxlevel;  //跳跃表允许的最大级数
    int levels;    //已存在的非空层数
    SkipNode<E>* head;  //跳跃表的头指针
    SkipNode<E>* tail; //跳跃表的尾指针
    E Tail_key;  //限定节点的值在一定的范围中.
};
#endif
