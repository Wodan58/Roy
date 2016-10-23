#
#  Makefile for COY
#
cmake_minimum_required(VERSION 3.0)
project(Coy)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
FLEX_TARGET(MyScanner lexer.l lexer.c)
#add_definitions(-DBENCHMARK)
add_definitions(-DBIT_32 -Ofast -mno-red-zone -fno-omit-frame-pointer
		-Wall -Wextra -Werror -Wno-missing-field-initializers
		-Wno-sign-compare -fno-align-functions -fno-align-loops
		-fno-align-jumps -fno-align-labels -fno-exceptions
		-fno-builtin -fno-asynchronous-unwind-tables)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		node.c eval.c memory.c)
target_link_libraries(joy /usr/local/lib/libgc-lib.a)

add_executable(run run.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c)
target_link_libraries(run /usr/local/lib/libgc-lib.a)
add_custom_command(OUTPUT run.c
		   COMMAND joy -c <tutorial.joy >run.c
		   DEPENDS joy tutorial.joy)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt)
add_custom_target(demo2.txt ALL
		  COMMAND run >demo2.txt)

#add_executable(fib fib.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c)
#target_link_libraries(fib /usr/local/lib/libgc-lib.a)
#add_custom_command(OUTPUT fib.c
#		   COMMAND joy -c <fib.joy | clang-format >fib.c
#		   DEPENDS joy fib.joy)
