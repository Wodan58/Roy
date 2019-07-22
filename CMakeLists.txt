#
#  Makefile for Coy
#
cmake_minimum_required(VERSION 3.0)
project(Coy)
set(CMAKE_BUILD_TYPE Release)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
if(WIN32)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
endif()
include_directories(bdwgc/include)
add_subdirectory(bdwgc)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} yylex.c symbol.c builtin.c print.c)
target_link_libraries(joy gc-lib)
add_executable(run main.c run.c print.c lookup.c)
target_link_libraries(run gc-lib)
add_custom_command(OUTPUT run.c
		   COMMAND joy -c <tutorial.joy | clang-format >run.c
		   DEPENDS joy tutorial.joy)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt
		  DEPENDS joy tutorial.joy)
add_custom_target(demo2.txt ALL
		  COMMAND run >demo2.txt
		  DEPENDS run)
add_custom_target(compare ALL
		  COMMAND diff demo1.txt demo2.txt
		  DEPENDS demo1.txt demo2.txt)
