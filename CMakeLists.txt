cmake_minimum_required(VERSION 3.0.0)
project(mileStone2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CLI CLI.cpp Commands/ClassifyingCommand.cpp Commands/ConfusionMatrixCommand.cpp Commands/DownloadCommand.cpp Commands/PrintingCommand.cpp Commands/SettingsCommand.cpp Commands/UploadCommand.cpp DefaultIO.hpp StandardIO.cpp Classifier.cpp Data.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
