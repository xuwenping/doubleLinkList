all:
	gcc -g -fPIC -shared darray.c -o libdarray.so
	gcc -g -DDARRAY_TEST darray.c -o darray_test
	gcc -g -DSORT_TEST sort.c -o sort_test -O0
	gcc -g -DQSEARCH_TEST search.c -o search_test -O0

clean:
	rm -f *test *.exe *.so 
