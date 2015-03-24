all:
	gcc -g -fPIC -shared darray.c -o libdarray.so
	gcc -g -DDARRAY_TEST darray.c -o darray_test -g

clean:
	rm -f *test *.exe *.so 
