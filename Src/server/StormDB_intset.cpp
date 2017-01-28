/*************************************************************************
	> File Name: StormDB_intset.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月15日 星期日 21时10分02秒
 ************************************************************************/

using namespace std;
#include "StormDB_intset.h"

Intset::Intset(){
    counts = 0; 
    bit_size =0;
    encoding = INTSET_ENC_INT16;
}
//析构函数
Intset::~Intset(){
    
}
//一组重载的向集合插入元素函数
void 
Intset::Insert(short s){
    if(encoding == INTSET_ENC_INT16){
        v1.push_back(s);
    }else if(encoding == INTSET_ENC_INT32){
        v2.push_back(s);
    }else if(encoding == INTSET_ENC_INT64){
        v3.push_back(s);
    }
}
void 
Intset::Insert(int s){
    if(encoding == INTSET_ENC_INT16){
        for(auto &temp : v1){
            v2.push_back(temp);
        }
        v2.push_back(s);
        encoding = INTSET_ENC_INT32;
    }else if(encoding == INTSET_ENC_INT32){
        v2.push_back(s);
    }else if(encoding == INTSET_ENC_INT64){
        v3.push_back(s);
    }
}
void 
Intset::Insert(long s){
    if(encoding == INTSET_ENC_INT64){
        for(auto &temp : v1){
            v3.push_back(temp);
        }
    }else if(encoding == INTSET_ENC_INT32){
        for(auto &temp : v2){
            v3.push_back(temp);
        }
    }
    encoding = INTSET_ENC_INT64; //一旦有一个long类型值插入集合就必须为long类型,改变encoding.
    v3.push_back(s);
}
void
Intset::Insert(std::string s){
    v4.push_back(s);
}

//输出集合函数
void
Intset::print_int(){
    if(encoding == INTSET_ENC_INT16){
        for(auto &temp : v1){
            std::cout << temp << std::endl;
        }    
    }
    if(encoding == INTSET_ENC_INT32){
        for(auto &temp : v2){
            std::cout << temp <<std::endl;
        }
    }
    if(encoding == INTSET_ENC_INT64){
        for(auto &temp : v3){
            std::cout << temp <<std::endl;
        }
    }
    //如果整数和字符同时存在,将整数和字符串都输出.整数在前.
    for(auto &temp : v4){
        std::cout << temp <<std::endl;
    }
}
//对集合中的元素按照升序排序
int 
Intset::sortAscedOrder(){
    if(encoding == INTSET_ENC_INT16){
        sort(v1.begin(),v1.end(),less<short>());
    }
    if(encoding == INTSET_ENC_INT32){
        sort(v2.begin(),v2.end(),less<int>());
    }
    if(encoding == INTSET_ENC_INT64){
        sort(v3.begin(),v3.end(),less<long>());
    }
    //给字符串元素按升序排序
    sort(v4.begin(),v4.end(),less<std::string>());
    return 0;
}
//对集合的元素按降序排序
int 
Intset::sortDescendOrder(){
    if(encoding == INTSET_ENC_INT16){
        sort(v1.begin(),v1.end(),greater<short>());
    }
    if(encoding == INTSET_ENC_INT32){
        sort(v2.begin(),v2.end(),greater<int>());
    }
    if(encoding == INTSET_ENC_INT64){
        sort(v3.begin(),v3.end(),greater<long>());
    }
    //给字符串元素按升序排序
    sort(v4.begin(),v4.end(),greater<std::string>());
    return 0;
    
}
//返回集合包含的元素
int 
Intset::getSize(){
    if(encoding == INTSET_ENC_INT16){
        counts = v1.size();
    }
    if(encoding == INTSET_ENC_INT32){
        counts = v2.size();
    }
    if(encoding == INTSET_ENC_INT64){
        counts = v3.size();
    }
    counts += v4.size(); //算出整数和字符元素的总个数.
    return counts;
}
int 
Intset::getBitSize(){
    if(encoding == INTSET_ENC_INT16){
        bit_size = v1.size()*2;
    }
    if(encoding == INTSET_ENC_INT32){
        bit_size = v2.size()*4;
    }
    if(encoding == INTSET_ENC_INT64){
        bit_size = v3.size()*8;
    }
    for(auto &temp : v4){
        std::cout << sizeof(temp) <<std::endl;
        bit_size += temp.size();
    }
    return bit_size;

}
//一组重载的从集合中移除给定元素的函数
bool Intset::IntsetDelete(short s){
    if(encoding != INTSET_ENC_INT16){
        std::cout << "The element or element type that is not exist!"<<std::endl;
        return false;
    }
    for(auto i = v1.begin();i != v1.end();++i){
        if(*i == s){
            v1.erase(i);
            break;
        }
    }
    return true;
}
bool Intset::IntsetDelete(int s){
    if(encoding != INTSET_ENC_INT32){
        std::cout << "The element or element type that is not exist!"<<std::endl;
        return false;
    }
    for(auto i = v2.begin();i != v2.end();++i){
        if(*i == s){
            v2.erase(i);
            break;
        }
    }
    return true;
    
}
 bool Intset::IntsetDelete(long s){
    if(encoding != INTSET_ENC_INT64){
        std::cout << "The element or element type that is not exist!"<<std::endl;
        return false;
    }
    for(auto i = v3.begin();i != v3.end();++i){
        if(*i == s){
            v3.erase(i);
            break;
        }
    }
    return true;

}
bool
Intset::IntsetDelete(std::string s){
    for(auto i = v4.begin();i != v4.end();i++){
        if(*i == s){
            v4.erase(i);
            break;
        }
    }
    return true;
}
//一组重载的在集合中查找指定的元素的函数
bool Intset::findIntset(short s){
    if(encoding == INTSET_ENC_INT32){
        int m = s;
        return findIntset(m);
    }
    if(encoding == INTSET_ENC_INT64){
        long m = s;
        return findIntset(m);
    }
    this->sortAscedOrder();
    int found = 0;
    int mid;
    int low = 0;
    int high = v1.size();
    while(low <= high){
        mid = (high + low)/2;
        auto i = v1.begin()+mid;
        if(*i == s){
            found = 1;
            break;
        }
        if(*i < s){
            low = mid+1; //mid往右移动
        }else{
            high = mid-1; //mid往左移动
        }
    }
    if(found){
        return true;
    }
    std::cout << "Find the element does not exist" <<std::endl;
    return false;
}
bool
Intset::findIntset(int s){
    if(encoding == INTSET_ENC_INT32){
        long m = s;
        return findIntset(m);
    }
    if(encoding == INTSET_ENC_INT16){
        std::cout << "Find the element does not exist" <<std::endl;
        return false;
    }
    this->sortAscedOrder();
    int found = 0;
    int mid;
    int low = 0;
    int high = v2.size();
    while(low <= high){
        mid = (high + low)/2;
        auto i = v2.begin()+mid;
        if(*i == s){
            found = 1;
            break;
        }
        if(*i < s){
            low = mid+1; //mid往右移动
        }else{
            high = mid-1; //mid往左移动
        }
    }
    if(found){
        return true;
    }
    std::cout << "Find the element does not exist" <<std::endl;
    return false;
}
bool
Intset::findIntset(long s){
    if(encoding != INTSET_ENC_INT64){
        std::cout << "Find the element does not exist" <<std::endl;
        return false;
    }
    this->sortAscedOrder();
    int found = 0;
    int mid;
    int low = 0;
    int high = v3.size();
    while(low <= high){
        mid = (high + low)/2;
        auto i = v3.begin()+mid;
        if(*i == s){
            found = 1;
            break;
        }
        if(*i < s){
            low = mid+1; //mid往右移动
        }else{
            high = mid-1; //mid往左移动
        }
    }
    if(found){
        return true;
    }
    std::cout << "Find the element does not exist" <<std::endl;
    return false;
}
bool Intset::findIntset(std::string s){
    
    
    this->sortAscedOrder();
    int found = 0;
    int mid;
    int low = 0;
    int high = v4.size();
    while(low <= high){
        mid = (high + low)/2;
        auto i = v4.begin()+mid;
        if(*i == s){
            found = 1;
            break;
        }
        if(*i < s){
            low = mid+1; //mid往右移动
        }else{
            high = mid-1; //mid往左移动
        }
    }
    if(found){
        return true;
    }
    std::cout << "Find the element does not exist" <<std::endl;
}
