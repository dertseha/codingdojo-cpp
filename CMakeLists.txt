cmake_minimum_required (VERSION 3.0...3.15)
project (codingdojo)
enable_testing()

if (NOT WIN32) #linux
	SET(Runtime_LIBRARIES pthread)
endif (WIN32)

include_directories(${PROJECT_SOURCE_DIR}/src/main)

add_library(dojo STATIC)
target_sources(dojo PRIVATE ./src/main/DummyClass.cpp)

include_directories(${PROJECT_SOURCE_DIR}/lib/gmock)
add_library(gmock STATIC lib/gmock/gmock-gtest-all.cc)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN} lib/gmock/gmock_main.cc)
    target_link_libraries(${TESTNAME} dojo gmock ${Runtime_LIBRARIES})
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(UnitTests ${LIB_TEST_SOURCE})
target_sources(UnitTests PRIVATE ./src/test/DummyTest.cpp)