#
#   module  : CMakeLists.txt
#   version : 1.3
#   date    : 06/21/20
#

#
#   C version
#
add_executable(fib0 fib0.c)

#
#   Regression test
#
add_custom_target(test00.txt ALL
		  DEPENDS joy
		  COMMAND make -f regres.mak)

#
#   Minimal version
#
macro(exe1 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${src}.joy
		   COMMAND joy -c ${src}.joy 2>../runtime.h |
			   clang-format >${src}.c)
add_executable(${src} ../main.c ${src}.c ../print.c)
target_link_libraries(${src} gc-lib m)
endmacro(exe1)

#
#   Normal version: yylex.c, factor.c, module.c, lookup.c added.
#
macro(exe2 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${src}.joy
		   COMMAND joy -c ${src}.joy 2>../runtime.h |
			   clang-format >${src}.c)
add_executable(${src} ../main.c ${src}.c ../print.c ../yylex.c ../factor.c
	       ../module.c ../lookup.c)
target_link_libraries(${src} gc-lib m)
endmacro(exe2)

#
#   Special version: Normal and Long version
#
macro(exe3 src)
add_custom_command(OUTPUT ${src}.c
		   DEPENDS joy ${src}.joy
		   COMMAND joy -l ${src}.joy 2>../runtime.h |
			   clang-format >${src}.c)
add_executable(${src} ../main.c ${src}.c ../print.c ../yylex.c ../factor.c
	       ../module.c ../lookup.c)
target_link_libraries(${src} gc-lib m)
endmacro(exe3)

exe1(fib)
exe1(gcd)
exe1(test1)
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
exe1(plgtst)
exe2(tutorial)
exe2(joytut)
exe3(lsptst)
