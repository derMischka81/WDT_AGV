CFLAGS=-Wall -Wstrict-prototypes -O2

test_wdt: test_wdt.o
	gcc -pthread -o test_wdt test_wdt.o -L/usr/lib -lwdt_dio

test_wdt.o: test_wdt.c
	gcc -c $(CFLAGS) -I../../include test_wdt.c

clean:
	rm -f test_wdt.o test_wdt
