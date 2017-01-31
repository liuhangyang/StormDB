CC = clang++ -std=c++11
CGLAGS  = -Wall -g 
MY_LIBS = -lpthread
eylib:Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Epoll.o Server.o test_Server.o
	${CC} ${CGLAGS} -o eylib Base_loop.o Buffer.o Event_loop.o Event_loop_thread_pool.o Server.o  test_Server.o Epoll.o ${MY_LIBS} && rm *.o
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
test_Server.o:Server.o Connection.h 
	${CC} ${CGLAGS} -c test_Server.cpp
.PHONY: clean
clean:
	rm *.o


