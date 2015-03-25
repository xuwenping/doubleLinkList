all:
	gcc -g -fPIC -shared darray.c -o libdarray.so
	gcc -g -DDARRAY_TEST darray.c -o darray_test -g
	gcc -g -DSORT_TEST sort.c -o sort_test -g -O0

clean:
	rm -f *test *.exe *.so 
