.PHONY: default driver log all sample deploy install clean

CC = gcc
CFLAGS = -O2 -D_GNU_SOURCE -Wall -Wstrict-prototypes -I./ -fPIC -fvisibility=hidden -fno-strict-aliasing

define ld_path
	if [ `/bin/uname -s` == 'Linux' ]; then \
	  if [ `/bin/uname -m` == 'x86_64' ] && [ -d '/usr/lib64' ]; then \
	    echo /usr/lib64; \
	  else \
	    echo /usr/lib; \
	  fi; \
	fi
endef

LIBRARY_PATH := $(shell $(ld_path))
DEPLOY_PATH := $(shell pwd)/linux/deploy/$(shell uname -r).$(shell uname -m)
SAMPLE_PATH := $(shell pwd)/linux/sample

default: libwdt_dio.so

driver:
	cd $(shell pwd)/linux/driver && make clean && make default && cd ../../

log: CFLAGS += -D__LOG_CONSOLE
log:
	rm -f *.o libwdt_dio.so libwdt_dio.d.so *~
	gcc $(CFLAGS) -c libwdt_dio.c
	gcc -shared -o libwdt_dio.d.so -L$(LIBRARY_PATH) libwdt_dio.o
	if [ -e libwdt_dio.d.so ]; then cp -f libwdt_dio.d.so $(DEPLOY_PATH); fi;

all: clean
all: default
all: deploy
all: install
all: log
all: driver
all: sample

sample:
	if [ ! -d $(DEPLOY_PATH) ]; then mkdir -p $(DEPLOY_PATH); fi;
	for f in $(shell ls -d $(SAMPLE_PATH)/*/); do cd $$f; make clean; \
	if [ -e `basename $$f`.pro ]; then rm -f Makefile; qmake-qt5 `basename $$f`.pro; qmake-qt5; fi; \
	make && cp -f `basename $$f` $(DEPLOY_PATH)/; \
	done

.c.o: $.c
	gcc $(CFLAGS) -c $<

libwdt_dio.so: libwdt_dio.o
	gcc -shared -o libwdt_dio.so -L$(LIBRARY_PATH) libwdt_dio.o

deploy:
	if [ ! -d $(DEPLOY_PATH) ]; then mkdir -p $(DEPLOY_PATH); fi; \
	if [ -e libwdt_dio.so ]; then cp -f libwdt_dio.so $(DEPLOY_PATH); fi; \

install:
	echo $(LIBRARY_PATH) && sudo cp -f libwdt_dio.so $(LIBRARY_PATH)

clean:
	rm -f *.o libwdt_dio.so libwdt_dio.d.so *~
