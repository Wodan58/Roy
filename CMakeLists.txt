#
#   module  : CMakeLists.txt
#   version : 1.8
#   date    : 03/01/21
#
cmake_minimum_required(VERSION 3.0)
project(Coy VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)
option(RUN_TESTS "Run standard tests" ON)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
if(WIN32)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
endif()
include_directories(. bdwgc/include)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} print.c builtin.c symbol.c
	       yylex.c factor.c module.c optable.c srand.c rand.c tmpfile.c)
target_link_libraries(joy gc-lib m)
add_dependencies(joy always)
add_custom_target(always
		  COMMAND sh banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh prims.sh
		  COMMAND sh trans.sh
		  COMMAND sh table.sh)
#
#  Standard tests
#
if(RUN_TESTS)
add_executable(run main.c run.c print.c yylex.c factor.c module.c lookup.c)
target_link_libraries(run gc-lib m)
add_custom_command(OUTPUT run.c
		  COMMAND joy -c <tutorial.joy 2>runtime.h | clang-format >run.c
		  DEPENDS joy tutorial.joy)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt
		  DEPENDS joy tutorial.joy)
add_custom_target(demo2.txt ALL
		  COMMAND run <input.txt >demo2.txt
		  DEPENDS run runtime.h)
add_custom_target(compare ALL
		  COMMAND diff demo1.txt demo2.txt
		  DEPENDS demo1.txt demo2.txt)
endif()
#
#  Fibonacci benchmark
#
if(RUN_TESTS)
add_executable(fib1a main.c fib1a.c print.c)
target_link_libraries(fib1a gc-lib m)
add_custom_command(OUTPUT fib1a.c
		   COMMAND joy -c <fib1a.joy 2>runtime.h | clang-format >fib1a.c
		   DEPENDS joy fib1a.joy runtime.h)
add_subdirectory(lib)
add_subdirectory(test)
endif()
add_subdirectory(bdwgc)
