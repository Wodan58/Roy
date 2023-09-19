#
#   module  : CMakeLists.txt
#   version : 1.1
#   date    : 09/19/23
#
cmake_minimum_required(VERSION 3.0)
project(Roy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
option(RUN_TESTS "Run standard tests" OFF)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
endif()
add_definitions(-DJVERSION="${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
add_executable(fib fib.c exeterm.c ersatz.c main.c exec.c writ.c)
add_dependencies(fib always)
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/defs.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/deps.sh ${CMAKE_SOURCE_DIR}
		 )
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
  target_link_libraries(fib gc-lib)
  include_directories(bdwgc/include)
  add_subdirectory(bdwgc)
else()
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
  endif()
  target_link_libraries(fib m gc)
  if(RUN_TESTS)
    add_subdirectory(test2)
  endif()
endif()
