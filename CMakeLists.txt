cmake_minimum_required (VERSION 2.6)
project (codingdojo)

if (WIN32)

else (WIN32) #linux

	SET(Runtime_LIBRARIES pthread)

endif (WIN32)

include_directories(${PROJECT_SOURCE_DIR}/src/main)

file(GLOB_RECURSE LIB_SOURCE src/main/*.c*)
add_library(dojo STATIC ${LIB_SOURCE})

include_directories(${PROJECT_SOURCE_DIR}/lib/gmock)

add_library(gmock STATIC lib/gmock/gmock-gtest-all.cc)

file(GLOB_RECURSE LIB_TEST_SOURCE src/test/*.c*)
add_executable(dojo-test ${LIB_TEST_SOURCE} lib/gmock/gmock_main.cc)
target_link_libraries(dojo-test dojo gmock ${Runtime_LIBRARIES})
