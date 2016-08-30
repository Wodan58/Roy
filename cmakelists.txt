#
#  Makefile for COY
#
cmake_minimum_required(VERSION 3.0)
project(Coy)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
find_package(FLEX)
FLEX_TARGET(MyScanner lexer.l lexer.c)
add_executable(joy main.c ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS}
		node.c eval.c memory.c)
target_link_libraries(joy /usr/local/lib/libgc-lib.a)
add_executable(run run.c ${FLEX_MyScanner_OUTPUTS} node.c memory.c)
target_link_libraries(run /usr/local/lib/libgc-lib.a)
add_custom_target(run.c DEPENDS joy tutorial.joy)
add_custom_command(OUTPUT run.c COMMAND joy -c <tutorial.joy >run.c)
add_custom_target(demo1.txt ALL
		  COMMAND joy <tutorial.joy >demo1.txt
		  DEPENDS joy tutorial.joy)
add_custom_target(demo2.txt ALL
		  COMMAND run >demo2.txt
		  DEPENDS run)
