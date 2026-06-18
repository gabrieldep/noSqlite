cmake_minimum_required(VERSION 4.2)
project(noSqlite)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(noSqlite apps/cli/main.cpp
        src/core/storage/services/PageManager.cpp
        src/core/storage/types/PageHeader.h
        src/core/memory/interfaces/IBufferPoolManager.h
        src/core/memory/types/FrameMetadata.h
        src/core/memory/services/BufferPoolManager.cpp
)

target_include_directories(noSqlite PRIVATE src)
