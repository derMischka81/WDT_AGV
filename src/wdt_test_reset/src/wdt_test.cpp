#include <cstdio>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <string>
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

//BOOL __cdecl InitWDT(void);
//BOOL __cdecl StopWDT(void);
//BOOL __cdecl StartWDT(void);
//BOOL __cdecl SetWDT(WORD tick, BYTE unit);
//BOOL __cdecl ResetWDT(void);


using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "agv_wdt_reset");
    ros::NodeHandle nh;
    ros::Rate loop_rate(1);
    ros::NodeHandle n;

    if (!InitWDT()) {
        printf("InitWDT <-- ERROR\n");
        return -1;
    }
    if (!SetWDT(5, 1)) {
        printf("SetWDT <-- ERROR\n");
        return -1;
    }
    if (!StartWDT()) {
        printf("StartWDT <-- ERROR\n");
        return -1;
    }
    printf("The Watch-dog Timer was activated\n");

    int i = 0;

//    for ( i=0; 20 > i; ++i ) {
//        printf("just pass %2d seconds\n", i);
//        sleep(1);
//    }
//
//    ResetWDT();
//    StopWDT();
//    return 0;


//while (ros::ok()) {
    while (1) {
        ROS_INFO("%d seconds passed", ++i);
    if (!StopWDT()) {
        printf("StartWDT <-- ERROR\n");
        return -1;
    }
    if (!ResetWDT()) {
        printf("StartWDT <-- ERROR\n");
        return -1;
    }
if (!SetWDT(5, 1)) {
        printf("SetWDT <-- ERROR\n");
        return -1;
    }
    if (!StartWDT()) {
        printf("StartWDT <-- ERROR\n");
        return -1;
    }
        ROS_INFO("reset\n");

        ros::spinOnce();
//        sleep(1);
        loop_rate.sleep();
    }
}


