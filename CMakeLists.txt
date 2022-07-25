#
#   module  : CMakeLists.txt
#   version : 1.16
#   date    : 07/25/22
#
cmake_minimum_required(VERSION 3.0)
project(Coy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
set(CMAKE_BUILD_TYPE "Debug")
endif()
if(WIN32)
option(WINDOWS "Use _MSC_VER compiler" ON)
endif()
option(REAL_BDW "Use BDW garbage collector" OFF)
option(RUN_TESTS "Run standard tests" ON)
find_package(BISON)
BISON_TARGET(MyParser parse.y parse.c)
if(WINDOWS)
add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
else()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage") # debug, no optimization
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
endif()
endif()
if(REAL_BDW)
add_definitions(-DGC_BDW -DJVERSION="BDW ${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
include_directories(bdwgc/include . ${CMAKE_SOURCE_DIR})
add_executable(joy main.c ${CMAKE_SOURCE_DIR}/${BISON_MyParser_OUTPUTS} print.c
               builtin.c symbol.c tmpfile.c module.c yylex.c factor.c optable.c
               compile.c arity.c identify.c compare.c)
if(WINDOWS)
target_link_libraries(joy gc-lib)
else()
target_link_libraries(joy gc-lib m)
endif()
add_subdirectory(bdwgc)
else()
add_definitions(-DJVERSION="MINGC ${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
include_directories(. ${CMAKE_SOURCE_DIR})
add_executable(joy main.c ${CMAKE_SOURCE_DIR}/${BISON_MyParser_OUTPUTS} print.c
               builtin.c symbol.c tmpfile.c module.c yylex.c factor.c optable.c
               compile.c arity.c identify.c compare.c gc.c)
if(WINDOWS)
target_link_libraries(joy ws2_32)
else()
target_link_libraries(joy m)
endif()
endif()
add_dependencies(joy always)
if(WINDOWS)
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prims.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/table.sh ${CMAKE_SOURCE_DIR})
else()
add_custom_target(always
		  COMMAND sh ${CMAKE_SOURCE_DIR}/banner.sh ${PROJECT_NAME} ${PROJECT_VERSION}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/prims.sh ${CMAKE_SOURCE_DIR}
		  COMMAND sh ${CMAKE_SOURCE_DIR}/table.sh ${CMAKE_SOURCE_DIR})
if(RUN_TESTS)
#add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(test2)
endif()
endif()
