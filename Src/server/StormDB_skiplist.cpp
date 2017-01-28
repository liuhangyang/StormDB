/*************************************************************************
	> File Name: StormDB_skiplist.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月21日 星期三 21时01分20秒
 ************************************************************************/
#include "StormDB_skiplist.h"
#include<iostream>

/**
 *构造函数,large表示节点允许的最大值
 */
 template<class E>
 list_skip<E>::list_skip(E large,int MaxE,float p){
    Tail_key = large;
    maxlevel = ceil(log(MaxE)/log(1/p))-1;
    levels = 0;
    
    //创建头节点,尾节点.
    head = new SkipNode<E>(maxlevel+1);
    tail = new  SkipNode<E>(maxlevel+1);

    //让头节点的每个指针都先指在tail这块地方
    tail->setData(large);
     for(int i = 0; i <= maxlevel; ++i){
         head -> forward[i] = tail;
     }
 }
 //析构函数
 template<class E>
 list_skip<E>::~list_skip(){
     SkipNode<E> *next;
     //通过删除0级链的所有节点.
     while(head != tail){
         next = head->forward[0]; //forward[0]中是0级下一个元素的地址.
         delete head;
         head = next;
     }
     delete tail;
 }
 //产生一个随机级号<=maxlevel;
 template <class E>
 int list_skip<E>::Rlevel(){
     int level = 0;
     while(rand()%2){
        level++;
     }
     return (level <= maxlevel)?level:maxlevel;
 }
 //向跳跃表插入元素
 template<class E>
 int list_skip<E>::Insert(E pData){
     //值太大或者已经存在
     if(pData >= Tail_key || this -> Search(pData)){
         return 0;
     }
     //创建一个新的节点,并将其初始化
     SkipNode<E>* newNode = new SkipNode<E>(maxlevel+1);
     newNode->setData(pData);
     for(int i = 0;i <= maxlevel; ++i){
         newNode->forward[i] = tail;
     }
     //为新节点创建级号
     int leval = Rlevel();
     std::cout << "level = "<< leval <<" levels = "<< levels <<std::endl;

     //如果随机出来的层数大于已存在的非空层,则增加一层
     int key_level = ((leval >= levels)? levels : leval);
     if(leval > levels){
         ++levels;
    }
     
     //建立一个指针数组保存每层要插入数据的位置
     SkipNode<E>** update = new SkipNode<E>*[maxlevel];
     SkipNode<E>* p = head;
     SkipNode<E>* q = NULL;
     

     //从高往低查找处合适的位置然后插入
     for(int i = key_level; i >= 0;--i){
         while((q = p->forward[i]) != tail && q -> getData() < pData){
             p = q;
         }
         update[i] = p; //把新元素插入到p元素之后.
     }
     for(int i = key_level; i >= 0;--i){
         newNode->forward[i] = update[i]->forward[i];
         update[i]->forward[i] = newNode;
     }
     delete[] update;

 }
 //从跳跃表中删除指定的值
 template<class E>
 bool list_skip<E>::Delete(E pData){
     SkipNode<E>* p = head;
     SkipNode<E>* q = NULL;
     for(int i = levels; i >= 0;--i){
         while((q = p->forward[i]) != tail && q->getData() <= pData){
             if(q->getData() == pData){
                 for(int j = 0;j <= levels; ++j){
                     p->forward[j] = q->forward[j];
                 }
                 delete q;
                 return true;
             }
             p = q;
         }
     }
     return false;
 }
//在跳跃表中查找指定的值

template<class E>
E list_skip<E>::Search(E pData){
    SkipNode<E>* p = head;
    SkipNode<E>* q = NULL;
    for(int i = levels;i >= 0;--i){
        while((q = p->forward[i]) != tail && q->getData() <= pData){
            if(q->getData() == pData){
                return pData;
            }
            p = q;
        }
    }
    return 0;
}
//输出跳跃表的内容
template<class E>
void list_skip<E>::print(){
    SkipNode<E> * temp = NULL;
    for(int i = 0;i <= levels;++i){
        temp = head->forward[i];
        std::cout << "层数:####->:"<<i<<" ";
        while(temp != tail){
            std::cout  << temp->getData() << "->";
            temp = temp -> forward[i];      
        }
        std::cout << std::endl;
    }
}
/*int main(int argc,char *argv[])
{
    list_skip<long> temp(10000);
    for(long i = 0; i < 30;i++){
        temp.Insert(i);
    }
    temp.print();
    temp.Delete(5);
    temp.Delete(4);
    temp.print();
    long p = temp.Search(6);
    std::cout << p<<std::endl;
    long q = temp.Search(5);
    std::cout << q<<std::endl;
   return 0;
}*/
