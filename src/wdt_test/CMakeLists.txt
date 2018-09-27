cmake_minimum_required(VERSION 2.8.3)
project(wdt_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
std_srvs
message_generation
)
#add_message_files(
#    DIRECTORY
#    msg
#  FILES
#  call_grasp.msg
#grasp_status.msg
#)

catkin_package(
  CATKIN_DEPENDS
    std_msgs
message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}/../../devel/include/
)

add_executable(wdt_test_node src/wdt_test.cpp)

target_link_libraries(wdt_test_node
  ${catkin_LIBRARIES}
)

