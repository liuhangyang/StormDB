/*************************************************************************
	> File Name: StormDB_CVirtualNode.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2016年12月24日 星期六 22时57分43秒
 ************************************************************************/

#include"StormDB_CVirtualNode.h"
#include<iostream>
CVirtualNode::CVirtualNode(CNode *pNode){
    node = pNode;
}
void 
CVirtualNode::setNode(CNode* pNode){
    node = pNode;
}
CNode* 
CVirtualNode::getNode(){
    return node;
}
void 
CVirtualNode::setHash(long pHash){
    hash = pHash;
}
long 
CVirtualNode::getHash(){
    return hash;
}

