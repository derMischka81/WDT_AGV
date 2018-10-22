CFLAGS=-Wall -Wstrict-prototypes -O2

test_cos: test_cos.o
	gcc -pthread -o test_cos test_cos.o -L/usr/lib -lwdt_dio

test_cos.o: test_cos.c
	gcc -c $(CFLAGS) -I../../include test_cos.c

clean:
	rm -f test_cos.o test_cos
