/*************************************************************************
	> File Name: test_StormDB_DB.cpp
	> Author:yanglongfei 
	> Mail:yanglongfei@xiyoulinux.org 
	> Created Time: 2017年01月18日 星期三 21时10分03秒
 ************************************************************************/

#include<iostream>
#include "../StormDB_KV.h"
#include "../StormDB_DB.h"
using namespace std;
int main(int argc,char *argv[])
{
    StormDB DB(4,10);
    KeyVal k("0",0,0);
    KeyVal k1("1",0,0);
    KeyVal k2("2",0,0);
    KeyVal k3("3",0,0);
    KeyVal k4("4",0,0);
    KeyVal k5("5",0,0);
    KeyVal k6("6",0,0);
    KeyVal k7("7",0,0);
    KeyVal k8("8",0,0);
    KeyVal k9("9",0,0);
    KeyVal k10("10",0,0);
    KeyVal k11("11",0,0);
    KeyVal k12("12",0,0);
    KeyVal k13("13",0,0);
    KeyVal k14("14",0,0);
    KeyVal k15("15",0,0);
    KeyVal k16("16",0,0);
    KeyVal k17("17",0,0);
    KeyVal k18("18",0,0);
    KeyVal k19("19",0,0);
    KeyVal k20("20",0,0);
    KeyVal k21("21",0,0);
    KeyVal k22("22",0,0);
    KeyVal k23("23",0,0);
    KeyVal k24("24",0,0);
    KeyVal k25("25",0,0);
    KeyVal k26("26",0,0);
    KeyVal k27("27",0,0);
    KeyVal k28("28",0,0);
    KeyVal k29("29",0,0);
    KeyVal k30("30",0,0);
    KeyVal k31("31",0,0);
    KeyVal k32("32",0,0);
    KeyVal k33("33",0,0);
    KeyVal k34("34",0,0);
    
    DB.StormDBAdd(k);
    DB.StormDBAdd(k1);
    DB.StormDBAdd(k2);
    DB.StormDBAdd(k3);
    DB.StormDBAdd(k4);
    
    //DB.StormDBDel(k4.GetKey());
    DB.StormDB_Show();
    DB.StormDBAdd(k5);
    DB.StormDBAdd(k6);
    DB.StormDBAdd(k7);
    DB.StormDBAdd(k8);
    DB.StormDB_Show();
    DB.StormDBAdd(k9);
    DB.StormDBAdd(k10);
    DB.StormDBAdd(k11);
    DB.StormDBAdd(k12);
    DB.StormDBAdd(k13);
    DB.StormDBAdd(k14);
    DB.StormDBAdd(k15);
    DB.StormDB_Show();
    DB.StormDBAdd(k16);
    DB.StormDB_Show();
    DB.StormDBAdd(k17);
    DB.StormDB_Show();
    DB.StormDBAdd(k18);

    DB.StormDBAdd(k19);
    DB.StormDBAdd(k20);
    DB.StormDBAdd(k21);
    DB.StormDBAdd(k22);
    DB.StormDBAdd(k23);
    DB.StormDBAdd(k24);
    DB.StormDBAdd(k25);
    DB.StormDBAdd(k26);
    DB.StormDBAdd(k27);
    DB.StormDBAdd(k28);
    DB.StormDBAdd(k29);
    DB.StormDBAdd(k30);
    DB.StormDBAdd(k31);
    DB.StormDBAdd(k32);
    DB.StormDB_Show();
    DB.StormDBAdd(k33);
    DB.StormDBAdd(k34);
    
    
    
    DB.StormDBDel(k1.GetKey());
    DB.StormDBDel(k2.GetKey());
    DB.StormDBDel(k3.GetKey());
    DB.StormDBDel(k4.GetKey());
    DB.StormDBDel(k5.GetKey());
    DB.StormDBDel(k6.GetKey());
    DB.StormDB_Show();
    DB.StormDBDel(k7.GetKey());
    DB.StormDBDel(k8.GetKey());
    DB.StormDBDel(k9.GetKey());
    DB.StormDBDel(k10.GetKey());
    DB.StormDBDel(k11.GetKey());
    DB.StormDBDel(k12.GetKey());
    DB.StormDBDel(k13.GetKey());
    DB.StormDB_Show();
    DB.StormDBDel(k14.GetKey());
    DB.StormDBDel(k15.GetKey());
    DB.StormDBDel(k16.GetKey());
    DB.StormDBDel(k17.GetKey());
    DB.StormDBDel(k18.GetKey());
    DB.StormDBDel(k19.GetKey());
    DB.StormDBDel(k20.GetKey());
    DB.StormDBDel(k21.GetKey());
    DB.StormDB_Show();
    DB.StormDBDel(k22.GetKey());
    DB.StormDBDel(k23.GetKey());
    DB.StormDBDel(k24.GetKey());
    DB.StormDBDel(k25.GetKey());
    DB.StormDBDel(k26.GetKey());
    DB.StormDBDel(k27.GetKey());
    DB.StormDBDel(k28.GetKey());
    DB.StormDBDel(k29.GetKey());
    DB.StormDBDel(k30.GetKey());
    DB.StormDBDel(k31.GetKey());
    DB.StormDB_Show();
    DB.StormDBDel(k33.GetKey());
    DB.StormDBDel(k34.GetKey());
    DB.StormDB_Show();
return 0;
}
