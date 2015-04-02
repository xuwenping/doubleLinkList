all:
	gcc -g -fPIC -shared dlist.c locker_pthread.c -o libdlist.so
	gcc -g -DDLIST_TEST dlist.c locker_pthread.c -lpthread -o dlist_test -O0
	gcc -g -DLOCK_TEST dlist.c produce_consume_model.c -lpthread -o lock_test -O0

clean:
	rm -f *test *.exe *.so
