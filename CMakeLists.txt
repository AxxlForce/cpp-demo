cmake_minimum_required(VERSION 3.7)
project(cpp_demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_demo
        src/main.cpp
        src/Interfaces/IService.h
        src/Interfaces/ILoggingService.h
        src/Interfaces/IUdpTransceiverService.h
        src/Interfaces/IFilesystemInputOutputService.h
        src/LoggingService/LoggingService.cpp
        src/LoggingService/LoggingService.h
        src/ServiceManager/ServiceManager.cpp
        src/ServiceManager/ServiceManager.h
        src/Application.cpp
        src/Application.h
        src/Reuse/Singleton/Singleton.h
        src/Reuse/AbsService/AbsService.cpp
        src/Reuse/AbsService/AbsService.h
        src/FilesystemInputOutputService/IFilesystemInputOutputService.cpp
        src/FilesystemInputOutputService/FilesystemInputOutputService.h
        src/UdpTransceiverService/UdpTransceiverService.cpp
        src/UdpTransceiverService/UdpTransceiverService.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(cpp_demo Threads::Threads)
