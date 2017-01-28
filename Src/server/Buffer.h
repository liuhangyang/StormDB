/*************************************************************************
	> File Name: Buffer.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 11时44分42秒
 ************************************************************************/

#ifndef _BUFFER_H
#define _BUFFER_H
#include "Endian.h"
#include <endian.h>
#include <string>
#include <vector>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
namespace eylib{
    class Buffer{
        public:
        static const int initialSize = 10240;
        Buffer():buffer_(initialSize),readerIndex_(0),writeIndex_(0){
            assert(buffer_.size() == initialSize);
            assert(readerIndex_ == 0);
            assert(writeIndex_ == 0);
        }
        ~Buffer(){}
        void getposLength(int length,char *buffer){
            memcpy(buffer,getReadPeek(),length);
        }
        int readableSize(){ //可读字节数
            return writeIndex_ - readerIndex_;
        }
        int writeableSize(){ //可写字节数
            return buffer_.size() - writeIndex_;
        }
        int recyclableSize(){
            return readerIndex_;
        }
        void append(const char* data,int len){
            makeSureEnough(len); //确保空间可写

            std::copy(data,data + len,getWritePeek());//将data中的数据拷贝到buffer中去.
            moveWriteIndex(len);
        }
        void getData(char* data,int length){
            std::copy(getReadPeek(),getReadPeek()+length,data);
            moveReadIndex(length);
        }
        void append(const void *data,int len){
            append((char *)data,len);
        }
        void append(const std::string &data){
            append(data.c_str(),data.size());
        }

        //添加整形数
        void appendInt64(int64_t x){
            int64_t be64 = hostToNetwork64(x);
            append(&be64,sizeof(be64));
        }
        void appendInt32(int32_t x){
            int32_t be32 = hostToNetwork32(x);
            append(&be32,sizeof(be32));
        }
        void appendInt16(int16_t x){
            int16_t be16 = hostToNetwork16(x);
            append(&be16,sizeof(be16));
        }
        int64_t peekInt64(){
            assert(readableSize() >= sizeof(int64_t));
            int64_t be64 = 0;
            memcpy(&be64,getReadPeek(),sizeof(be64));
            printf("be64:%ld\n",be64);
            return networkToHost64(be64);
        }
        int32_t peekInt32(){
            assert(readableSize() >= sizeof(int32_t));
            int32_t be32 = 0;
            memcpy(&be32,getReadPeek(),sizeof(be32));
            return networkToHost32(be32);
        }
        int16_t peekInt16(){
            assert(readableSize() >= sizeof(int16_t));
            int16_t be16 = 0;
            memcpy(&be16,getReadPeek(),sizeof(be16));
            return networkToHost16(be16);
        }
        int getHeadLength(){
            char headbuf[4];
            bzero(headbuf,4);
            memcpy(headbuf,getReadPeek(),4);
           /* std::cout << headbuf <<std::endl;
            printf("[0]%c\n",headbuf[0]);
            printf("[1]%c\n",headbuf[1]);
            printf("[2]%c\n",headbuf[2]);
            printf("[3]%c\n",headbuf[3]);*/
            int a = (int)(headbuf[0] & 0x7f);
            int b = (int)(headbuf[1] & 0x7f)*128;
            int c = (int)(headbuf[2] & 0x7f)*16384;
            int d = (int)(headbuf[3] & 0x7f)*2097152;
            moveReadIndex(4);
            return a+b+c+d;

        }
        std::string intToByte(std::string &Str){
            int length =Str.size();
            char arr[4];
            arr[0] = (char)(length & 0x7f);
            arr[1] = (char)((length >> 7)&0x7f);
            arr[2] = (char)((length >> 14)&0x7f);
            arr[3] = (char)((length >> 21)&0x7f);
            std::string str;
            for(int i =0;i < 4;i++){
                str += arr[i];
            }
            str += Str;
            return str;
        }
        char *getReadPeek(){ //获得可读位置.
            return begin() + readerIndex_;
        }
        char *getWritePeek(){ //获得可写位置.
            return begin() + writeIndex_;
        }
        void moveWriteIndex(int len){ //移动写下标位置,用户不必调用,append自动调用.
            writeIndex_  += len;
        }
        void moveReadIndex(int len){ //移动读下标位置,外部从buffer读完以后由用户调用.
            readerIndex_ += len;
        }

        void makeSureEnough(int len){
            if(len > writeableSize()){
                if((recyclableSize() + writeableSize()) >= len){
                    copySpace(len);
                }else{
                    buffer_.resize(buffer_.size() + len); //还会留有大于0小于len的空间可写大小
                }
            }
        }
        int readFromFd(int fd); //从套接字中读取数据
        int writeToFd(int fd); //往套接字里写数据

        private:
        char *begin(){
            return &*buffer_.begin();
        }
        void copySpace(size_t len){
            std::copy(begin() + readerIndex_,begin() + writeIndex_,begin());
            readerIndex_ = 0;
            writeIndex_ = readableSize(); 
        }
        private:
            std::vector<char> buffer_;
            int readerIndex_;
            int writeIndex_;
    };
}
#endif
