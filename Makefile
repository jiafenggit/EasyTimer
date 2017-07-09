# A simple timer in C++

CC                  =   g++
CFLAGS              =   -std=c++14  -O2 -fPIC -pipe  -pedantic  -Wformat=2 
OBJS                =   timerengine.o

all:    ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} main.cpp -o main
	-rm *.o
        
timerengine.o:
	${CC} ${CFLAGS} ${LIBS}  -c -o timerengine.o timerengine.cpp

clean:
	rm -vf *.o 
	rm -rf main
