# -----------------------------------------
cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{CILK_SRC}/cilk_tests/cmake/Modules/")

include(CilkTestsCommon)
include(TargetDistclean)

#get all of the c and cpp files in the current directory
file(GLOB SRC 
  "*.c"
  "*.cpp")


#for each source file, make it an executable filename and add it as an executable target
foreach(f ${SRC})
  string(REGEX REPLACE ".cpp$|.c$" ".exe" loc ${f})
  get_filename_component(exec ${loc} NAME)
  add_executable(${exec} ${f})

  if($ENV{CCILK_PROFILE})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -g -DCCILK_PROFILE")
    target_link_libraries(${exec} dl pthread cilkrts ${LIBEVENT_LIBS1} ${LIBEVENT_LIBS2} ${PROFILER})
  else()
    target_link_libraries(${exec} dl pthread cilkrts ${LIBEVENT_LIBS1} ${LIBEVENT_LIBS2})
  endif()

  list(APPEND executables "build/${exec}")
endforeach(f)

install(PROGRAMS ${executables} DESTINATION "${CMAKE_SOURCE_DIR}/bin")



