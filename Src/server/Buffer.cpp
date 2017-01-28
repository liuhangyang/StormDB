/*************************************************************************
	> File Name: Buffer.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月06日 星期五 17时36分47秒
 ************************************************************************/

#include "Buffer.h"
#include <sys/uio.h> //readv
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
using namespace eylib;
int Buffer::readFromFd(int fd){ //作为inputBuffer从套接字中读取数据到buffer中
        if(writeableSize() > 1024*10){
        int count = read(fd,getWritePeek(),writeableSize());
        assert(count >= 0);

        writeIndex_ += count;
        return count;
    }else{
        char extrabuf[65536];
        struct iovec vec[2];

        int writeable = writeableSize();
        vec[0].iov_base = getWritePeek();
        vec[0].iov_len = writeableSize();
        vec[1].iov_base = extrabuf;
        vec[1].iov_len = sizeof(extrabuf);

        int count = readv(fd,vec,2);
        printf("cout------------------------->>>>>>>>>>>>:%d\n",count);
        assert(count >= 0);
        
        if(count <= writeableSize()){
            writeIndex_ += count;
        }else{ //buffer不够用,有部分数据在栈中,在将其添加到buffer中.
            writeIndex_ = buffer_.size();
            append(extrabuf,count - writeable);
        }
        return count;
        
    }
        return 0;
}
int
Buffer::writeToFd(int fd) //作为outputBuffer将buffer中的数据写入到套接字中
{
    int count = write(fd,getReadPeek(),readableSize()); //将buffer中的数据写入fd中;
    assert(count >= 0);

    moveReadIndex(count);
    return count; 
}
