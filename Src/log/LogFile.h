/*************************************************************************
mZ	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月04日 星期三 18时12分48秒
 ************************************************************************/

#ifndef _LOGFILE_H
#define _LOGFILE_H
namespace eylib{
    class LogFile{
    public:
        LogFile(int rollSize);
        ~LogFile();
        //往磁盘里添加消息
         void append(char *log,int len);
         void rollFile(int curLen);
    private:
        int rollSize_; //文件滚动大小
        int fd_;
        int fillSize_; //当前文件填充大小. 
        int fileNumbers_; //已有文件数量.
    };
}
#endif
