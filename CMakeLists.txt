#
#  Makefile for COY
#
cmake_minimum_required(VERSION 3.0)
project(Coy)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
if(WIN32)
FLEX_TARGET(MyScanner lexer.l lexer.c COMPILE_FLAGS --wincompat)
else()
FLEX_TARGET(MyScanner lexer.l lexer.c)
endif()
add_definitions(-DDEBUG -DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS -DBIT_32)
include_directories(bdwgc/include)
add_subdirectory(bdwgc)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		eval.c node.c memory.c builtin.c)
target_link_libraries(joy gc-lib)
add_executable(run run.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c builtin.c)
target_link_libraries(run gc-lib)
add_custom_command(OUTPUT run.c
		   COMMAND joy -c <tutorial.joy >run.c
		   DEPENDS joy tutorial.joy)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt
		  DEPENDS joy tutorial.joy)
add_custom_target(demo2.txt ALL
		  COMMAND run <input.txt >demo2.txt
		  DEPENDS run)
add_custom_target(compare ALL
		  COMMAND diff demo1.txt demo2.txt
		  DEPENDS demo1.txt demo2.txt)
