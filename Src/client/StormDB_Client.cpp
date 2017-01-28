/*************************************************************************
	> File Name: StormDB_Client.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月21日 星期六 21时41分08秒
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include "./StormDB_Client.h"
#include <vector>
std::pair<std::string,int> arr[]={
    std::make_pair("SET",0),
    std::make_pair("GET",1),
    std::make_pair("DEL",2),
    std::make_pair("HSET",3),
    std::make_pair("HDEL",5),
    std::make_pair("HGETALL",6),
    std::make_pair("LSET",7),
    std::make_pair("LGET",8),
    std::make_pair("LPUSH",9),
    std::make_pair("LPOP",10),
    std::make_pair("RPUSH",11),
    std::make_pair("RPOP",12),
    std::make_pair("INCR",13),
    std::make_pair("DECR",14),
    std::make_pair("APPEND",15)
};
StrToInt Client::IntMap(arr,arr + sizeof(arr)/sizeof(arr[0]));
Client::Client(void){
    _init(IP,PORT);
}
Client::Client(const std::string &host){
    _init(host,PORT);
}
Client::Client(const std::string &host, int port){
    _init(host,port);
}
Client::~Client(void){
    close(_socket);
}
void 
Client::set(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_ok_reply();
}
void
Client::get(const std::vector<std::string> &data){
    //std::cout <<(Command()<<data).getbuffer()<<std::endl;
    _send((Command()<<data).getbuffer());
    _recv_string_reply();
    //return "";

}
void
Client::del(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_int_reply();
}
void Client::append(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    char buf[1024];
    char buf1[1024];
    bzero(buf,sizeof(buf));
    bzero(buf1,sizeof(buf1));
    int num = read(_socket,buf,1024);
    if(buf[0]== '+'){
        strcpy(buf1,buf+1);
        printf("%s",buf1);
    }
    if(buf[0] == '-'){
        strcpy(buf1,buf+1);
        printf("%s",buf1);
    }
    if(buf[0] == ':'){
        strcpy(buf1,buf+1);
        std::string Str("");
        Str += "(integer):";
        Str += buf1;
        std::cout << Str;
    }
}
void
Client::hset(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_ok_reply();
}
void
Client::hdel(const std::vector<std::string> &data){
    _send((Command()  <<data).getbuffer());
    _recv_int_reply();
}
void
Client::hgetall(const std::vector<std::string> &data,string_vector &fields,string_vector &values){
    _send((Command() << data).getbuffer());
    string_vector all;
    _recv_multi_bulk_reply(all);

}
void
Client::_recv_multi_bulk_reply(string_vector all){
    char buf[1024];
    int num = read(_socket,buf,1024);
    if(strcmp(buf,"(nil)\r\n") == 0){
        printf("%s",buf);
    }else{
    std::vector<std::string> items;
    split(buf,"\r\n",items);
    std::cout << "items.size: "<<items.size() <<std::endl;
    int t=1;
    for(int i=2;i<items.size()-3;i=i+4){
        std::cout <<"(" <<t <<") " <<"key: " <<items[i] <<"    "<<"value: "<< items[i+2] <<std::endl;
        t++;
    }
    }
}
void 
Client::lset(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_ok_reply();
}
void 
Client::lget(const std::vector<std::string> &data){
    _send((Command() << data ).getbuffer());
}

void
Client::lpush(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_ok_reply();
}
void
Client::lpop(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
    _recv_string_reply();
}
void 
Client::rpush(const std::vector<std::string> &data){
    _send((Command() <<data).getbuffer());
    _recv_ok_reply();
}
void
Client::rpop(const std::vector<std::string> &data){
    _send((Command() <<data).getbuffer());
    _recv_string_reply();
}
void 
Client::incr(const std::vector<std::string> &data){
    _send((Command() << data).getbuffer());
}
void
Client::decr(const std::vector<std::string> &data){
    _send((Command() <<data).getbuffer());
}
void Client::_recv_ok_reply(){
    char buf[1024];
    char buf1[1024];
    bzero(buf,sizeof(buf));
    bzero(buf1,sizeof(buf1));
    int num = read(_socket,buf,1024);
    if(buf[0] == '+'){
        strcpy(buf1,buf+1);
        printf("%s",buf1);    
    }else{
        strcpy(buf1,buf+1);
        printf("%s",buf1);
        
    }
}
void Client::_recv_string_reply(){
    std::vector<std::string> items;
    char buf[1024];
    bzero(buf,sizeof(buf));
    int num = read(_socket,buf,1024);
    split(buf,"\r\n",items);
    //printf("items.szie: %ld\n",items.size());
    std::cout << items[0] <<std::endl;
}
void Client::_recv_int_reply(){
    std::string Str("");
    char buf[1024];
    bzero(buf,sizeof(buf));
    int num = read(_socket,buf,1024);
    Str += "(integer)";
    Str +=buf;
    std::cout << Str;
}
void
Client::_recv_rlpop_reply(){
    std::vector<std::string> items;
    char buf[1024];
    bzero(buf,sizeof(buf));
    int num = read(_socket,buf,1024);
    split(buf,"\r\n",items);
    std::cout << items[1] << std::endl;
}
bool 
Client::input(std::vector<std::string> &str){
    int i = 0;
    std::cout << IP <<  ":" << PORT << ">";
    std::string temp;
    std::getline(std::cin,temp);
    char str1[1024];
    temp.append("\n");
    int j = 0;
    for(int i= 0;i<temp.size();i++){
        if(temp[i] == '\n'){
            if(strlen(str1) > 0){
                str1[j] = '\0';
                str.push_back(str1);
            }
            break;
        }else if(temp[i] == ' '){
            if(strlen(str1) >0){
                str1[j]= '\0';
                str.push_back(str1);
            }
            j = 0;
            str1[0]='\0';
        }else{
            str1[j] = temp[i];
            j++;
        } 
    }
    const char* result; 
    Judge judge;
    result  = judge.JudgeCommand(str[0],str.size()-1);
    if(strcmp(result,"OK") == 0){
        return true;
    }else{
        std::cout << result <<std::endl;
        return false;   
    }
}
void
Client::start(){
    for(;;){
        std::vector<std::string> str;
        string_vector fields;
        string_vector values;
        if(input(str)){
            toUpper(str[0]);
            if(strcmp(str[0].c_str(),"QUIT")==0){
                break;
            }
            int t = IntMap[str[0]];
            //printf("yanglongfei\n");
            switch(t){
                case 0:
                    set(str);
                    break;
                case 1:
                    get(str);
                    break;
                case 2:
                    del(str);
                    break;
                case 3:
                    hset(str);
                    break;
                case 5:
                    hdel(str);
                    break;
                case 6:
                    hgetall(str,fields,values);
                    break;
                case 7:
                    lset(str);
                    break;
                case 8:
                    lget(str);
                    break;
                case 9:
                    lpush(str);
                    break;
                case 10:
                    lpop(str);
                    break;
                case 11:
                    rpush(str);
                    break;
                case 12:
                    rpop(str);
                    break;
                case 13:
                    incr(str);
                    break;
                case 14:
                    decr(str);
                    break;
                case 15:
                    append(str);
                    break;
                default:
                    break;
        }   }
    }
}
void
Client::_init(const std::string &host,int port){
    int value =1;
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET,host.c_str(),&serveraddr.sin_addr);
    _socket = socket(AF_INET,SOCK_STREAM,0);
    setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR,&value,sizeof(value));
    int ret = connect(_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(ret < 0){
        perror("error:socket connect!");
        exit(1);
    }
}
std::string 
Client::intToByte(int length){
    char arr[4];
     arr[0]=(char)(length & 0x7f);
     arr[1]=(char)((length >> 7)&0x7f);
     arr[2]=(char)((length >>14)&0x7f);
     arr[3]=(char)((length >>21)&0x7f);
        //printf("%d\n",arr[0]);
        std::string Str;
        for(int i=0;i<4;i++){
           // printf("ddddd%d",arr[i]);
            Str+=arr[i];
        }
       // printf("\n");
        //printf("byte:%d\n",strlen(arr));
       // std::cout << "Str:" <<Str<<"  "<<Str.size()<<std::endl;
        return Str;
}
void 
Client::_send(const std::string& msg){
    //printf("dddd\n");
    int m= msg.size();
    std::string strlength;
    strlength = intToByte(m);
    strlength += msg;
   /* std::cout << "strlength:" <<strlength <<std::endl;
    printf("[0]%c\n",strlength[0]);
    printf("[1]%c\n",strlength[1]);
    printf("[2]%c\n",strlength[2]);
    printf("[3]%c\n",strlength[3]);
    char buf[1024];
    printf("----------%d\n",strlen(strlength.c_str()));
    memcpy(buf,strlength.c_str(),4);
    strcat(buf,msg.c_str());
    printf("buf:%s\n",buf);
    //char buf[1024];*/
    //std::cout << "strlength: "<< strlength <<std::endl;
    int t = write(_socket,strlength.c_str(),strlength.size());
    //printf("&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    //printf("t=%d\n",t);
    //read(_socket,buf,1024);
    //printf("%s\n",buf);
}


