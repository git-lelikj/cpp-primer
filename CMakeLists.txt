project(cpp_primer)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# add extra flags to CFLAGS and CXXFLAGS
set (EXTRA_CXXFLAGS "-std=c++11")
set (COMMON_CFLAGS_WARNINGS "-Wall -Wextra -Wno-unused-parameter -Werror-implicit-function-declaration -Wno-format -Wno-unknown-pragmas -Wno-long-long -Wchar-subscripts -Wcomment -Wformat -Wformat-nonliteral -Wformat-security -Wformat=2 -Wmissing-braces -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wunknown-pragmas -Wfloat-equal -Wundef -Wshadow -Wwrite-strings -Wconversion -fno-inline")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CXXFLAGS} ${COMMON_CFLAGS_WARNINGS}")
