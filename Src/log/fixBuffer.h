/*************************************************************************
	> File Name: fixBuffer.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 17时20分01秒
 ************************************************************************/

#ifndef _FIXBUFFER_H
#define _FIXBUFFER_H
#include <vector>
namespace eylib{
    class FixBuffer{
    public:
        FixBuffer():buffer_(1024*1024*4){
            readableIndex_ = 0;
            writeableIndex_ = 0;
        }
        ~FixBuffer(){
            
        }
        int readableSize(void){ //可读字节数.
            return writeableIndex_ - readableIndex_;
        }
        int writeableSize(void){ //可写字节数.
            return buffer_.size() - writeableIndex_;
        }
        void append(const char* data,int len){
            std::copy(data,data+len,getWritePeek());
            moveWriteIndex(len);
        }
        char *getReadPeek(void){ //获得写位置的指针
            return begin() + readableIndex_;
        }
        char *getWritePeek(void){ //获得读位置
            return begin() + writeableIndex_;
        }
        void moveWriteIndex(int len){ //移动可写下标.
            writeableIndex_ = writeableIndex_ + len;
        }
        void resetBuffer(void){ //重置buffer;
            readableIndex_ = 0;
            writeableIndex_ = 0;
        }
    private:
    char *begin(){
        return &*buffer_.begin();
    }
        std::vector<char> buffer_;
        int readableIndex_;
        int writeableIndex_;
    };
}
#endif
