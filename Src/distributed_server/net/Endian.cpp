/*************************************************************************
	> File Name: Endian.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 10时28分21秒
 ************************************************************************/
#include "Endian.h"
#include <endian.h>
#include <stdint.h>
#include <stdio.h>
    uint64_t hostToNetwork64(uint64_t host64){
        return htobe64(host64);
    }
    uint32_t hostToNetwork32(uint32_t host32){
        return htobe32(host32);
    }
    uint16_t hostToNetwork16(uint16_t host16){
        return htobe16(host16);
    }
    uint64_t networkToHost64(uint64_t net64){
        return be64toh(net64);
    }
    uint32_t networkToHost32(uint32_t net32){
        return be32toh(net32);
    }
    uint16_t networkToHost16(uint16_t net16){
        return be16toh(net16);
    }
