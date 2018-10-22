cmake_minimum_required( VERSION 2.8 )
project ( test_wdt )

set( CMAKE_CXX_COMPILER "g++" )
#set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -O2" )

############### dependencies ######################

include_directories( ${PROJECT_SOURCE_DIR}/include )

link_directories(/usr/lib)


set( THIRD_PARTY_LIBS
        #    ${PROJECT_SOURCE_DIR}/libcontrolcan.so
        ${PROJECT_SOURCE_DIR}/libwdt_dio.so
        )
add_executable( test_wdt test_wdt.cpp )
#target_link_libraries( test_wdt  ${THIRD_PARTY_LIBS} )
target_link_libraries( test_wdt  libwdt_dio.so -lpthread)