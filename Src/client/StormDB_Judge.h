/*************************************************************************
	> File Name: StormDB_Judge.h
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月22日 星期日 11时15分26秒
 ************************************************************************/

#ifndef _STORMDB_JUDGE_H
#define _STORMDB_JUDGE_H
#include <map>
#include <string>
typedef std::map<std::string,int> StrInt;
class Judge{
public:
    Judge()=default;
    const char* JudgeCommand(std::string cmd, int arg);
    void toUpper1(std::string &str){
        for(int i = 0; i <str.length();i++){
            if(str[i] > 96 && str[i] <123){
                str[i] -= 32;
            }
        }
    }
private:
    static StrInt CmdMap;
};
#endif
