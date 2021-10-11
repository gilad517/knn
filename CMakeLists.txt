cmake_minimum_required(VERSION 3.0.0)
project(mileStone2 VERSION 0.1.0)
include(CTest)
enable_testing()

add_executable(Server Server.cpp CLI.cpp Commands/ClassifyingCommand.cpp Commands/ConfusionMatrixCommand.cpp Commands/DownloadCommand.cpp Commands/PrintingCommand.cpp Commands/SettingsCommand.cpp Commands/UploadCommand.cpp DefaultIO.h StandardIO.cpp SocketIO.cpp Classifier.cpp Data.cpp)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Server PRIVATE Threads::Threads)
add_executable(Client Client.cpp DefaultIO.h StandardIO.cpp SocketIO.cpp)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
