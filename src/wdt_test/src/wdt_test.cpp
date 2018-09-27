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

using namespace std;
int main(int argc, char **argv) {
 ros::init(argc, argv, "ur_twist_server");
  ros::NodeHandle nh;
 ros::Rate loop_rate(1);
  ros::NodeHandle n;


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
//
//    for ( i=0; 30 > i; ++i ) {
//        printf("just pass %2d seconds\n", i);
//        sleep(1);
//    }


    int  i=0;

while (ros::ok()) {
ROS_INFO("%d seconds passed",i);
    ResetWDT();

    ros::spinOnce();

    loop_rate.sleep();
  }
}


