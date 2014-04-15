export CPLUS_INCLUDE_PATH=/home/dyc
export CXXFLAGS=-g
objects=AsyncLogging.o Condition.o CountDownLatch.o Date.o Exception.o \
	FileUtil.o LogFile.o Logging.o LogStream.o ProcessInfo.o \
	Thread.o ThreadPool.o Timestamp.o TimeZone.o 

lib:$(objects)
	echo "done"
	ar -q libbase.a $(objects)

.PHONY: clean
clean:
	rm -rf *.o libbase.a
