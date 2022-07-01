cmake_minimum_required(VERSION 3.14)
project(dfa)

enable_testing()

add_subdirectory(src)
if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
