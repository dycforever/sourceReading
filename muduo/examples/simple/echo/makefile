CFLAGS=-g
INC=-I/home/dyc/
LIB=-L/home/dyc/muduo
main:main.cc echo.cc 
	g++ -I/home/dyc $(LIB) $(INC) $^ -o $@ -lmuduo -lpthread -lrt
