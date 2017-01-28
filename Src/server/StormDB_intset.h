/*************************************************************************
	> File Name: StormDB_intset.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 20时16分06秒
 ************************************************************************/

#ifndef _STORMDB_INTSET_H
#define _STORMDB_INTSET_H
#include <iostream>
#include <vector>
#include <functional>
#include <cstdio>
#include <algorithm>

#define INTSET_ENC_INT16 1
#define INTSET_ENC_INT32 2
#define INTSET_ENC_INT64 3
using namespace std;

class Intset{
private:
    long counts;   // 集合中包含的元素的个数.
    
    int bit_size; //集合所占字节数. 
    int encoding;
    //如果操作的元素是整数类型的
    std::vector<short> v1;
    std::vector<int> v2;
    std::vector<long> v3;
    
    std::vector<std::string> v4; //如果操作的元素是字符串类型的
public:
    //一组重载向集合插入函数
    void Insert(short s);
    void Insert(int s);
    void Insert(long s);
    void Insert(std::string s);

    //重载从集合中删除元素
    bool IntsetDelete(short s);
    bool IntsetDelete(int s);
    bool IntsetDelete(long s);
    bool IntsetDelete(std::string s);

    //构造函数
    Intset(); //构造函数
    ~Intset(); //析构函数

    void print_int(); //输出集合中的元素
    int getSize();  //返回集合中元素的个数
    int getBitSize(); //返回集合占用的内存字节数
    int sortAscedOrder(); //给集合按升序排序
    int sortDescendOrder();//给集合按降序排序

    //重载从集合中查找元素
    bool findIntset(short s);
    bool findIntset(int s);
    bool findIntset(long s);
    bool findIntset(std::string s);


};
#endif
