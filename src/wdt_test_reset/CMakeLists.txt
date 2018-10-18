cmake_minimum_required(VERSION 2.8.3)
project(wdt_test_reset)

#set( CMAKE_CXX_COMPILER "g++" )
#set( CMAKE_BUILD_TYPE "Release" )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -O2" )

link_directories(/usr/lib)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
std_srvs

)

catkin_package(
  CATKIN_DEPENDS
    std_msgs
message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
${PROJECT_SOURCE_DIR}/../../devel/include/
)

add_executable(wdt_test_reset_node src/wdt_test.cpp)

target_link_libraries(wdt_test_reset_node
  ${catkin_LIBRARIES}
        libwdt_dio.so -lpthread
)

