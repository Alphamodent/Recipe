cmake_minimum_required(VERSION 3.10)
project(Dark_age)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src(.cpp_file)/*.cpp")

add_executable(Dark_age ${SOURCES})
