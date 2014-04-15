
lib:
	make -C base -j8
	make -C net -j8
	make -C net/poller -j8
	ar -q libmuduo.a base/*.o net/*.o net/poller/*.o
	
.PHONY: clean
clean:
	make clean -C base 
	make clean -C net
	make clean -C net/poller 
	rm -rf libmuduo.a

