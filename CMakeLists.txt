cmake_minimum_required (VERSION 2.6)
project (codingdojo)
enable_testing()

if (NOT WIN32) #linux
	SET(Runtime_LIBRARIES pthread)
endif (WIN32)

include_directories(${PROJECT_SOURCE_DIR}/src/main)

file(GLOB_RECURSE LIB_SOURCE src/main/*.c*)
add_library(dojo STATIC ${LIB_SOURCE})

include_directories(${PROJECT_SOURCE_DIR}/lib/gmock)
add_library(gmock STATIC lib/gmock/gmock-gtest-all.cc)


file(GLOB_RECURSE LIB_TEST_SOURCE src/test/*.c*)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN} lib/gmock/gmock_main.cc)
    target_link_libraries(${TESTNAME} dojo gmock ${Runtime_LIBRARIES})
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(UnitTests ${LIB_TEST_SOURCE})