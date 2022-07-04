#
#   module  : CMakeLists.txt
#   version : 1.7
#   date    : 06/21/22
#

#
#	Note: assuming BDW version
#

#
#	Minimal version
#
macro(exe1 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -c ${CMAKE_SOURCE_DIR}/lib/${src}.joy |
                           clang-format >${src}.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}.c
               ${CMAKE_SOURCE_DIR}/print.c ${CMAKE_SOURCE_DIR}/lookup.c
               ${CMAKE_SOURCE_DIR}/compare.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe1)

#
#	Normal version: support for get
#
macro(exe2 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -c ${CMAKE_SOURCE_DIR}/lib/${src}.joy |
                           clang-format >${src}.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}//main.c ${src}.c
               ${CMAKE_SOURCE_DIR}/print.c ${CMAKE_SOURCE_DIR}/lookup.c
	       ${CMAKE_SOURCE_DIR}/yylex.c ${CMAKE_SOURCE_DIR}/factor.c
               ${CMAKE_SOURCE_DIR}/compare.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe2)

#
#	Library version, without support for get
#
macro(exe3 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -l ${CMAKE_SOURCE_DIR}/lib/${src}.joy |
                           clang-format >${src}.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}.c
               ${CMAKE_SOURCE_DIR}/print.c ${CMAKE_SOURCE_DIR}/lookup.c
               ${CMAKE_SOURCE_DIR}/compare.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe3)

#
#	Library version, including support for get
#
macro(exe4 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy
		   COMMAND joy -l ${CMAKE_SOURCE_DIR}/lib/${src}.joy |
                           clang-format >${src}.c)
add_executable(${src}1 ${CMAKE_SOURCE_DIR}/main.c ${src}.c
               ${CMAKE_SOURCE_DIR}/print.c ${CMAKE_SOURCE_DIR}/lookup.c
	       ${CMAKE_SOURCE_DIR}/yylex.c ${CMAKE_SOURCE_DIR}/factor.c
               ${CMAKE_SOURCE_DIR}/compare.c)
target_link_libraries(${src}1 gc-lib m)
endmacro(exe4)

#
#	Test interpreter
#
macro(exe5 src)
add_custom_target(${src}1.out ALL
		  DEPENDS joy
		  COMMAND joy ${CMAKE_SOURCE_DIR}/lib/${src}.joy 24 54 >${src}1.out)
endmacro(exe5)

#
#	Test compiled programs
#
macro(exe6 src)
add_custom_target(${src}2.out ALL
		  DEPENDS ${src}1
		  COMMAND ${src}1 24 54 >${src}2.out)
endmacro(exe6)

#
#	Test compiler
#
exe1(fib)
exe1(gcd)
exe1(test)
exe1(jp-joytst)
exe1(flatjoy)
exe1(jp-reprodtst)
exe1(modtst)
exe1(jp-nestrec)
exe1(laztst)
exe1(jp-church)
exe1(mtrtst)
exe1(grmtst)
exe1(reptst)
exe1(symtst)
exe2(tutorial)
exe3(plgtst)
exe4(joytut)
exe4(lsptst)

#
#	Test interpreter
#
exe5(fib)
exe5(gcd)
exe5(test)
exe5(jp-joytst)
exe5(flatjoy)
exe5(jp-reprodtst)
exe5(modtst)
exe5(jp-nestrec)
exe5(laztst)
exe5(jp-church)
exe5(mtrtst)
exe5(grmtst)
exe5(reptst)
exe5(symtst)
exe5(plgtst)
exe5(tutorial)
exe5(joytut)
exe5(lsptst)

#
#	Test compiled programs
#
exe6(fib)
exe6(gcd)
exe6(test)
exe6(jp-joytst)
exe6(flatjoy)
exe6(jp-reprodtst)
exe6(modtst)
exe6(jp-nestrec)
exe6(laztst)
exe6(jp-church)
exe6(mtrtst)
exe6(grmtst)
exe6(reptst)
exe6(symtst)
exe6(plgtst)

#
#	Rest of compiled programs
#
add_custom_target(tutorial2.out ALL
		  DEPENDS tutorial1
		  COMMAND tutorial1 ${CMAKE_SOURCE_DIR}/lib/tutorial.inp >tutorial2.out)

add_custom_target(lsptst2.out ALL
		  DEPENDS lsptst1
		  COMMAND lsptst1 ${CMAKE_SOURCE_DIR}/lib/lsptst.inp >lsptst2.out)

add_custom_target(joytut2.out ALL
		  DEPENDS joytut1
		  COMMAND joytut1 ${CMAKE_SOURCE_DIR}/lib/joytut.inp >joytut2.out)
