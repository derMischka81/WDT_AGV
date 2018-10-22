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
//#include <pthread.h>
 extern "C" {
#include "wdt_dio.h"
 }


int main(int argc, char **argv)
{
    int  i;

    if ( ! InitWDT() ) {
        printf("InitWDT <-- ERROR\n");
        return -1;
    }
    if ( ! SetWDT(10, 1) ) {
        printf("SetWDT <-- ERROR\n");
        return -1;
    }
    if ( ! StartWDT() ) {
        printf("StartWDT <-- ERROR\n");
        return -1;
    }
    printf("The Watch-dog Timer was activated\n");

    for ( i=0; 30 > i; ++i ) {
        printf("just pass %2d seconds\n", i);
        sleep(1);
    }

    return 0;
}
