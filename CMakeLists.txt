#
#   module  : CMakeLists.txt
#   version : 1.11
#   date    : 09/24/24
#
cmake_minimum_required(VERSION 3.5)
project(Roy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
add_executable(fib fib.c main.c exeterm.c writ.c print.c)
add_definitions(-DLINK="\\"${CMAKE_EXE_LINKER_FLAGS}\\"")
add_definitions(-DVERS="${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
#
#	MSVC: cmake --build . --config Release
#
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_VERBOSE_MAKEFILE ON)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGC_NOT_DLL -D_CRT_SECURE_NO_DEPRECATE")
  add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS}\\"")
  target_link_libraries(fib ../../joy1/gc-8.2.8/build/Release/gc)
else()
  add_dependencies(fib always)
  add_custom_target(always
		    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh .
		    COMMAND sh ${CMAKE_SOURCE_DIR}/defs.sh .
		    COMMAND sh ${CMAKE_SOURCE_DIR}/deps.sh .
		   )
  set(CF "-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CF}")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_RELEASE}\\"")
  else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CF} -g -O3 --coverage -fprofile-arcs -ftest-coverage")	# debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_DEBUG}\\"")
  endif()
  target_link_libraries(fib m gc)
endif()
