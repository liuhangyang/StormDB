CC = clang++ -std=c++11
CGLAGS = -Wall -g
MY_LIBS = -lpthread 
Server:StormDB_DB.o StormDB_DBAll.o StormDB_String.o StormDB_intset.o  StormDB_KV.o  Buffer.o Endian.o StormDB_Server.o StormDB_Epoll.o StormDB_Task.o Server.o  StormDB_Utils.o 
	${CC} ${CGLAGS} -o Server StormDB_DB.o StormDB_DBAll.o StormDB_String.o StormDB_intset.o  StormDB_Server.o StormDB_KV.o StormDB_Epoll.o Endian.o Buffer.o StormDB_Task.o StormDB_Utils.o Server.o  ${MY_LIBS} && rm *.o
StormDB_Utils.o:StormDB_Utils.hpp
	${CC} ${CGLAGS} -c StormDB_Utils.cpp

Endian.o:Endian.h
	${CC} ${CGLAGS} -c Endian.cpp
Buffer.o:Endian.o Buffer.h
	${CC} ${CGLAGS} -c Buffer.cpp
StormDB_intset.o:StormDB_intset.h
	${CC} ${CGLAGS} -c StormDB_intset.cpp
StormDB_KV.o:StormDB_Data_num.h StormDB_Hash_Map.h StormDB_Ziplist.h StormDB_String.o StormDB_Queue.h StormDB_Stack.h StormDB_intset.o 
	${CC} ${CGLAGS} -c StormDB_KV.cpp
StormDB_String.o:StormDB_String.h
	${CC} ${CGLAGS} -c StormDB_String.cpp
StormDB_DB.o:StormDB_KV.o StormDB_KV.h StormDB_DB.h
	${CC} ${CGLAGS} -c StormDB_DB.cpp
StormDB_DBAll.o:StormDB_DB.o StormDB_KV.o StormDB_DBAll.h
	${CC} ${CGLAGS} -c StormDB_DBAll.cpp
StormDB_Epoll.o:StormDB_Connect.h StormDB_Callback.h StormDB_Epoll.h
	${CC} ${CGLAGS} -c StormDB_Epoll.cpp
StormDB_Server.o: StormDB_DB.o StormDB_DBAll.o StormDB_KV.o StormDB_Callback.h StormDB_Epoll.o 
	${CC} ${CGLAGS} -c StormDB_Server.cpp
StormDB_Task.o: StormDB_DBAll.o StormDB_Connect.h StormDB_Task.h
	${CC} ${CGLAGS} -c StormDB_Task.cpp
Server.o: StormDB_Server.o StormDB_Connect.h StormDB_Utils.o ThreadPool.hpp StormDB_Task.o 
	${CC} ${CGLAGS} -c  Server.cpp
 


 


