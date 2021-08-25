cmake_minimum_required(VERSION 3.0.0)
project(mileStone2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(UdpServer UdpServer.cpp Classifier.cpp Iris.cpp)
add_executable(TcpServer TcpServer.cpp Classifier.cpp Iris.cpp)
add_executable(Client Client.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
