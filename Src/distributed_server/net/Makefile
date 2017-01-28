CC = clang++ -std=c++11
CGLAGS  = -Wall -g 
MY_LIBS = -lpthread
eylib:Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Epoll.o Server.o disServer.o Endian.o
	${CC} ${CGLAGS} -o eylib Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Server.o  disServer.o Epoll.o  Endian.o ${MY_LIBS} && rm *.o
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
disServer.o:Server.o Connection.h 
	${CC} ${CGLAGS} -c disServer.cpp
Endian.o:Endian.h
	${CC} ${CGLAGS} -c Endian.cpp
.PHONY: clean
clean:
	rm *.o


