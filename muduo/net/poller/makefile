export CPLUS_INCLUDE_PATH=/home/dyc
export CXXFLAGS=-g
objects=DefaultPoller.o EPollPoller.o PollPoller.o

lib:$(objects)
	ar -q libpoller.a $(objects)

.PHONY: clean
clean:
	rm -rf *.o libpoller.a
