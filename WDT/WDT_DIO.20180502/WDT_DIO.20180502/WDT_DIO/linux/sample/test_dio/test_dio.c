/*
 *  Nuvo-1000 Watch-dog Timer
 *
 *  Copyright (C) 2011 weiching.lin
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "wdt_dio.h"

int main(int argc, char *argv[])
{
    int  i, j;
    WORD  data = 0;

    if ( ! InitDIO() ) {
        printf("InitDIO <-- ERROR\n");
        return -1;
    }

    for (j=1; 3>j; j|=(j<<1)) {
        for (i=0; 8>i; ++i) {
            DOWritePort(j<<i);
            sleep(1);
            data = DIReadPort();
            printf("DIReadPort = 0x%hx\n", ~data);
        }
    }

    for (j=0x80; 0xd0>j; j|=(j>>1)) {
        for (i=0; 8>i; ++i) {
            DOWritePort(j>>i);
            sleep(1);
            data = DIReadPort();
            printf("DIReadPort = 0x%hx\n", ~data);
        }
    }

    return 0;
}
