#include <cstdio>
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <string>

using namespace std;
int main(int argc, char **argv) {
 ros::init(argc, argv, "ur_twist_server");
  ros::NodeHandle nh;
 ros::Rate loop_rate(10);
  ros::NodeHandle n;
while (ros::ok()) {
      
    ros::spinOnce();

    loop_rate.sleep();
  }
}


