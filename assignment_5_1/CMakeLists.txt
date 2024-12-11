cmake_minimum_required(VERSION 3.25)
project(assignment_5_1)

set(CMAKE_CXX_STANDARD 17)

find_package(cpprestsdk REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)

add_executable(assignment_5_1 main.cpp)

target_link_libraries(assignment_5_1 PRIVATE cpprestsdk::cpprest ${Boost_LIBRARIES} OpenSSL::SSL)
