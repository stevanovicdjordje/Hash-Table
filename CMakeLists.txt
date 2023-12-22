cmake_minimum_required(VERSION 3.24)
project(asp2dz3)

set(CMAKE_CXX_STANDARD 17)

add_executable(asp2dz3 main.cpp HashTable.h HashTable.cpp AddressFunction.h BidirectionalLinearAddressing.h BiderctionalLinearAddressing.cpp)
