
export LDFLAGS=-rdynamic
export CXXFLAGS=-g
export CFLAGS=-g
INC=-I/home/dyc/
LIB=-L/home/dyc/muduo

all:server client

server:main.cc time.cc
	g++ -g $(LIB) $(INC) $^ -rdynamic -o $@ -lmuduo -lpthread -lrt

client:timeclient.cc
	g++ -g $(LIB) $(INC) $^ -rdynamic -o $@ -lmuduo -lpthread -lrt

clean:
	rm server client
