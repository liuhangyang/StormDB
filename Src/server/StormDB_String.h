/*************************************************************************
	> File Name: StormDB_String.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月14日 星期六 22时42分07秒
 ************************************************************************/

#ifndef _STORMDB_STRING_H
#define _STORMDB_STRING_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#define STRING_MAX  1 << 12 //字符串的最大长度.
#define LEN(n) (n*2+1) //初始化时的空闲长度.
#define FREE(n) (LEN(n) - n)  //预分配一倍的额外的空间

#define DEFAULT_NULL 0 //默认空字符串的长度
#define DEFAULT_SIZE (1<<7)  //默认字符串的长度. 

class String{
    //重载部分运算符
    //重载'>','<','==','!='关系运算符
    friend bool operator<(const String &lhs,const String &rhs);
    friend bool operator>(const String &lhs,const String &rhs);
    friend bool operator==(const String &lhs,const String &rhs);
    friend bool operator!=(const String &lhs,const String &rhs);
    //重载输入输出运算符
    friend  std::ostream& operator<<(std::ostream &os,const String &rhs);
    friend std::istream& operator>>(std::istream &is,String &rhs);

    //重载相加运算符.
    friend String operator+(const String &lhs,const String &rhs);
    friend String operator+(const String &lhs,const char* rhs);
private:
    char *str;
    int size;
    int free;
public:
    String(char* rhs);
    String();
    String(const String &rhs);
    String(String &&rhs) noexcept;
    ~String();
    
    //重载运算符
    String & operator=(const String &rhs); //赋值运算符
    String &operator=(const char *rhs); //参数为char * 的赋值运算符.
    char& operator[](int i); //下标运算符.
    String& operator+=(const String &rhs); //复合赋值运算符.
    String& operator+=(const char* rhs); //行参为char *的复合赋值运算符.

    //接口函数
    int getSize() const; //获取当前字符串已用空间.
    int getFree() const; //获取字符串的空闲空间.
    void Print(); //打印字符串.
    String &StringAdd(const String &str2); //向字符串添加string类型的内容.
    String &StringAdd(const char* s); //向字符串添加char  *类型的内容
    String &StringClear(); //清除字符串的内容.
    String &StringSizeClear(size_t pos,size_t len); //以pos开始清除之后len长度的内容.
    String &StringChange(const char *s); //修改字符串为s;
    String &StringChange(const String &str2); //修改字符串为str2;
    char* StringGetChar();  

};
#endif
