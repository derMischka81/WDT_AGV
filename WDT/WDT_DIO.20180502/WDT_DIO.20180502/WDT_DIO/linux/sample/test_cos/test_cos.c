/*
 *  Neousys DI Change-of-State notification (DICOS)
 *
 *  Copyright (C) 2016 weiching.lin
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "wdt_dio.h"

void COS_Callback(COS_INT_CALLBACK_ARG* arg)
{
    printf("COS, data=0x%04x, flag=0x%04x\n", arg->portData, arg->intrFlag);
	return ;
}

int main(int argc, char *argv[])
{
	int  i, j;
	COS_INT_SETUP  setup;
	
	setup.portMask = 0xffff;
	setup.edgeMode = 0;
	setup.edgeType = 0;

    if ( ! RegisterCallbackDICOS(COS_Callback) ) {
        printf("RegisterCallbackDICOS <-- ERROR\n");
        return -1;
    }

    if ( ! SetupDICOS(&setup, sizeof(setup)) ) {
        printf("SetupDICOS <-- ERROR\n");
        return -2;
    }

    if ( ! StartDICOS() ) {
        printf("StartDICOS <-- ERROR\n");
        return -3;
    }

    for (j=0; 2>j; ++j) {
    	for (i=0; 60>i; ++i) {
            sleep(1);
            printf(".");
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }

    if ( ! StopDICOS() ) {
        printf("StopDICOS <-- ERROR\n");
        return -4;
    }

    return 0;
}
