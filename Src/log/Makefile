CC = clang++ -std=c++11
CGLAGS = -Wall -g
LDFLAGS = -pthread
Asny:AsyLog_test.o AsyLog.o LogFile.o 
	${CC} ${CGLAGS} -o Asny AsyLog_test.o AsyLog.o LogFile.o ${LDFLAGS} && rm *.o
AsyLog_test.o:AsyLog.h
	${CC} ${CGLAGS} -c AsyLog_test.cpp 
AsyLog.o:AsyLog.h LogFile.o fixBuffer.h
	${CC} ${CGLAGS} -c AsyLog.cpp
LogFile.o: LogFile.h
	${CC} ${CGLAGS} -c LogFile.cpp
.PHONY:clean
clean:
	rm *.o

