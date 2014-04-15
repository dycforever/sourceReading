INC=-I/home/dyc/
LIB=-L/home/dyc/muduo
download:download.cc
	g++ -g -I/home/dyc $(LIB) $(INC) $^ -o $@ -lmuduo -lpthread -lrt

.PHONY:clean
clean:
	rm -rf download
