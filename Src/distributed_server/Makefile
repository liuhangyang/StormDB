CC = clang++ -std=c++11
CGLAGS  = -Wall -g 
MY_LIBS = -lpthread
eylib:Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Epoll.o Server.o disServer.o Endian.o StormDB_Epoll.o StormDB_Md5.o StormDB_Md5_Hash.o StormDB_conf.o StormDB_conf.o  StormDB_CVirtualNode.o StormDB_distributed_Hash.o StormDB_CNode.o StormDB_Utils.o
	${CC} ${CGLAGS} -o eylib Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Server.o  disServer.o Epoll.o  Endian.o  StormDB_Epoll.o StormDB_Md5.o StormDB_Md5_Hash.o StormDB_conf.o StormDB_CVirtualNode.o StormDB_distributed_Hash.o StormDB_CNode.o StormDB_Utils.o ${MY_LIBS} && rm *.o
StormDB_Utils.o:StormDB_Utils.hpp
	${CC} ${CGLAGS} -c StormDB_Utils.cpp
Base_loop.o:Callback.h Event_loop_thread_pool.o Base_loop.h 
	${CC} ${CGLAGS} -c Base_loop.cpp
Buffer.o:Endian.h Buffer.h
	${CC} ${CGLAGS} -c Buffer.cpp
Event_loop.o:Event_loop.h Epoll.o Connection.h 
	${CC} ${CGLAGS} -c Event_loop.cpp
Event_loop_thread_pool.o:Event_loop_thread_pool.h Callback.h 
	${CC} ${CGLAGS} -c Event_loop_thread_pool.cpp
Server.o:Base_loop.o Callback.h
	${CC} ${CGLAGS} -c Server.cpp 
Endian.o:Endian.h
	${CC} ${CGLAGS} -c Endian.cpp
StormDB_conf.o:StormDB_conf.h
	${CC} ${CGLAGS} -c StormDB_conf.cpp
StormDB_Md5.o: StormDB_Md5.h
	${CC} ${CGLAGS} -c StormDB_Md5.cpp
StormDB_Md5_Hash.o:StormDB_Md5_Hash.h
	${CC} ${CGLAGS} -c StormDB_Md5_Hash.cpp
StormDB_CNode.o:StormDB_CNode.h
	${CC} ${CGLAGS} -c StormDB_CNode.cpp
StormDB_CVirtualNode.o:StormDB_CNode.o  StormDB_CVirtualNode.h
	${CC} ${CGLAGS} -c StormDB_CVirtualNode.cpp
StormDB_Epoll.o:Callback.h  Client.h StormDB_Epoll.h ObjectPool.h 
	${CC} ${CGLAGS} -c StormDB_Epoll.cpp
StormDB_distributed_Hash.o:Callback.h StormDB_CNode.o StormDB_CVirtualNode.o StormDB_conf.o StormDB_Md5.o StormDB_Md5_Hash.o StormDB_Epoll.o 
	${CC} ${CGLAGS} -c StormDB_distributed_Hash.cpp
disServer.o:Server.o Connection.h Client.h StormDB_distributed_Hash.o StormDB_Utils.o 
	${CC} ${CGLAGS} -c disServer.cpp
.PHONY: clean
clean:
	rm *.o


