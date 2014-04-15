export CPLUS_INCLUDE_PATH=/home/dyc
export CXXFLAGS=-g
objects=Acceptor.o boilerplate.o Buffer.o Channel.o Connector.o \
		EventLoop.o EventLoopThread.o EventLoopThreadPool.o InetAddress.o \
		Poller.o Socket.o SocketsOps.o TcpClient.o TcpConnection.o TcpServer.o Timer.o TimerQueue.o

lib:$(objects)
	ar -q libnet.a $(objects)

.PHONY: clean
clean:
	rm -rf *.o libnet.a

