cmake_minimum_required(VERSION 3.1)
project(Peacock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Peacock ${SOURCE_FILES} BOBHash.cpp hash_function.cpp md5.cpp key-value.cpp sha1.cpp PeacockHash.cpp)