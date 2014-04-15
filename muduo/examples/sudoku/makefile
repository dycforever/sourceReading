
INC=-I/home/dyc/
LIB=-L/home/dyc/muduo

all:server client

server:server_basic.cc sudoku.cc
	g++ $(LIB) $(INC) $^ -lmuduo -lpthread -lrt

client:client.cc sudoku.cc
	g++ $(LIB) $(INC) $^ -lmuduo -lpthread -lrt
