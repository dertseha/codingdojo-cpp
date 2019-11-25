cmake_minimum_required (VERSION 3.0...3.15)
project (codingdojo)
enable_testing()

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
target_compile_options(project-settings INTERFACE -std=c++17)

add_library(${PROJECT_NAME} STATIC)
set(PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main/DummyClass.cpp")
set(PROJECT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/main/DummyClass.h")
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_HEADERS} PRIVATE ${PROJECT_SOURCES})

##################################################################
### Apply all settings to current project                      ###
##################################################################
target_link_libraries(${PROJECT_NAME} PUBLIC project-settings)

add_library(gmock STATIC lib/gmock/gmock-gtest-all.cc)

macro(package_add_test TESTNAME SOURCES)
    add_executable(${TESTNAME} ${ARGN} lib/gmock/gmock_main.cc)
    target_link_libraries(${TESTNAME} PUBLIC project-settings ${PROJECT_NAME} gmock ${Runtime_LIBRARIES})
    target_include_directories(${TESTNAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/main" "${CMAKE_CURRENT_SOURCE_DIR}/lib/gmock")
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
    target_sources(UnitTests PRIVATE ${SOURCES})
endmacro()

SET(TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/DummyTest.cpp")
package_add_test(UnitTests ${LIB_TEST_SOURCE} ${TEST_SOURCES})
