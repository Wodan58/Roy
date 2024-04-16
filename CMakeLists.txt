#
#   module  : CMakeLists.txt
#   version : 1.3
#   date    : 04/13/24
#
cmake_minimum_required(VERSION 3.0)
project(Roy VERSION 1.0)
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()
add_definitions(-DLINK="\\"${CMAKE_EXE_LINKER_FLAGS}\\"")
add_definitions(-DVERS="${CMAKE_BUILD_TYPE} ${PROJECT_VERSION}")
add_executable(fib fib.c exeterm.c ersatz.c main.c writ.c)
#
#	MSVC: cmake --build . --config Release
#
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions(-DGC_NOT_DLL -D_CRT_SECURE_NO_WARNINGS)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  option(BUILD_SHARED_LIBS OFF)
  option(BUILD_TESTING OFF)
  option(build_cord OFF)
  option(enable_docs OFF)
  option(enable_threads OFF)
  option(enable_parallel_mark OFF)
  option(enable_thread_local_alloc OFF)
  option(enable_threads_discovery OFF)
  option(enable_throw_bad_alloc_library OFF)
  option(enable_gcj_support OFF)
  option(enable_java_finalization OFF)
  option(enable_atomic_uncollectable OFF)
  option(enable_disclaim OFF)
  option(enable_munmap OFF)
  option(enable_dynamic_loading OFF)
  option(enable_register_main_static_data OFF)
  option(enable_handle_fork OFF)
  option(install_headers OFF)
  option(disable_gc_debug ON)
  option(disable_single_obj_compilation ON)
  option(disable_handle_fork ON)
  option(without_libatomic_ops ON)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGC_NOT_DLL -D_CRT_SECURE_NO_DEPRECATE")
  add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS}\\"")
  target_link_libraries(fib bdwgc/Release/gc)
  include_directories(bdwgc/include)
  add_subdirectory(bdwgc)
else()
  add_dependencies(fib always)
  add_custom_target(always
		    COMMAND sh ${CMAKE_SOURCE_DIR}/prim.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/defs.sh ${CMAKE_SOURCE_DIR}
		    COMMAND sh ${CMAKE_SOURCE_DIR}/deps.sh ${CMAKE_SOURCE_DIR}
		   )
  set(CF "-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CF}")
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_RELEASE}\\"")
  else()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CF} -g -O0 --coverage -fprofile-arcs -ftest-coverage")	# debug, no optimization
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # enabling coverage
    add_definitions(-DCOMP="\\"${CMAKE_C_FLAGS_DEBUG}\\"")
  endif()
  target_link_libraries(fib m gc)
endif()
