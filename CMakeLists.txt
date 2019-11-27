cmake_minimum_required (VERSION 3.0...3.15)
project (codingdojo)

##################################################################
### Enable testing and add google test helpers                 ###
##################################################################
enable_testing()
include(${PROJECT_SOURCE_DIR}/cmake/AddGoogleTest.cmake)

##################################################################
### Adapt pthread for static/dynamic linking                   ###
##################################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG FALSE)
find_package(Threads)
if(TARGET Threads::Threads AND NOT BUILD_SHARED_LIBS)
    set_target_properties(Threads::Threads PROPERTIES INTERFACE_LINK_LIBRARIES "-Wl,--whole-archive ${CMAKE_THREAD_LIBS_INIT} -Wl,--no-whole-archive")
endif()

##################################################################
### Enable c++17 support                                       ###
##################################################################
add_library(project-settings INTERFACE)
target_compile_features(project-settings INTERFACE cxx_std_17)

##################################################################
### Define sources                                             ###
##################################################################
add_library(${PROJECT_NAME} STATIC)
set(PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main/DummyClass.cpp"
)
set(PROJECT_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main/DummyClass.h"
)

target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_HEADERS} PRIVATE ${PROJECT_SOURCES})

##################################################################
### Apply all settings to codingdojo lib                       ###
##################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC project-settings)
target_compile_options(${PROJECT_NAME} PRIVATE
                           $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall>
                           $<$<CXX_COMPILER_ID:MSVC>:-W4>
)

##################################################################
### Add tests                                                  ###
##################################################################
macro(package_add_test TESTNAME TESTSOURCES)
    add_executable(${TESTNAME} ${ARGN})
    add_gtest(${TESTNAME})
    target_include_directories(${TESTNAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/main")
    target_link_libraries(${TESTNAME} PUBLIC project-settings PRIVATE ${PROJECT_NAME})
    target_sources(${TESTNAME} PRIVATE ${TESTSOURCES})
endmacro()

SET(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/DummyTest.cpp")
package_add_test(UnitTests ${TEST_SOURCES})
