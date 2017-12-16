#
#  Makefile for COY
#
cmake_minimum_required(VERSION 3.0)
project(Coy)
set(CMAKE_BUILD_TYPE Debug)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
if(WIN32)
FLEX_TARGET(MyScanner lexer.l lexer.c COMPILE_FLAGS --wincompat)
else()
FLEX_TARGET(MyScanner lexer.l lexer.c)
endif()
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS -DBIT_32)
if(WIN32)
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")     # debug, no optimisation
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage") # enabling coverage
endif()
include_directories(bdwgc/include)
add_subdirectory(bdwgc)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		node.c eval.c memory.c)
if(WIN32)
target_link_libraries(joy gc-lib)
else()
target_link_libraries(joy gc-lib gcov)
endif()		
add_executable(fib fib.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c)
if(WIN32)
target_link_libraries(fib gc-lib)
else()
target_link_libraries(fib gc-lib gcov)
endif()	
add_custom_command(OUTPUT fib.c
		   COMMAND joy -c <fib.joy >fib.c
		   DEPENDS joy fib.joy)
add_executable(run run.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c)
if(WIN32)
target_link_libraries(run gc-lib)
else()
target_link_libraries(run gc-lib gcov)
endif()	
add_custom_command(OUTPUT run.c
		   COMMAND joy -c <tutorial.joy >run.c
		   DEPENDS joy tutorial.joy)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt)
add_custom_target(demo2.txt ALL
		  COMMAND run >demo2.txt)
