source=ngx_array.c ngx_buf.c ngx_conf_file.c ngx_connection.c ngx_cpuinfo.c ngx_crc32.c ngx_crypt.c ngx_cycle.c ngx_file.c ngx_hash.c ngx_inet.c ngx_list.c ngx_log.c ngx_md5.c ngx_murmurhash.c ngx_open_file_cache.c ngx_output_chain.c ngx_palloc.c ngx_parse.c ngx_queue.c ngx_radix_tree.c ngx_rbtree.c ngx_regex.c ngx_resolver.c ngx_shmtx.c ngx_slab.c ngx_spinlock.c ngx_string.c ngx_times.c

test_conf:test_conf.c
	make clean
	find ../../objs/ | grep ".o$$" | xargs ar rcs libngx.a 
	ar d libngx.a nginx.o
	gcc -O0 -g -I. -I../event/ -I../../objs/ -I../os/unix/ -I/home/dyc/tools/pcre/ \
		-L. -L/home/dyc/tools/pcre/.libs/ \
		-DTEST \
		nginx.c $< -o $@ -lngx -lpcre -lpthread -lcrypt

clean:
	rm -rf test_conf core
