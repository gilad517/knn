cmake_minimum_required(VERSION 3.0.0)
project(mileStone2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(udpServer udpServer.cpp Classifier.cpp Iris.cpp)
add_executable(tcpServer tcpServer.cpp Classifier.cpp Iris.cpp)
add_executable(client Client.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
