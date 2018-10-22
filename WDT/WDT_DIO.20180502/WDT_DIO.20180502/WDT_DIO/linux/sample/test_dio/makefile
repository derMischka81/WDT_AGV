CFLAGS=-Wall -Wstrict-prototypes -O2

test_dio: test_dio.o
	gcc -pthread -o test_dio test_dio.o -L/usr/lib -lwdt_dio

test_dio.o: test_dio.c
	gcc -c $(CFLAGS) -I../../include test_dio.c

clean:
	rm -f test_dio.o test_dio
