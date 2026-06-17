cmake_minimum_required(VERSION 4.2)
project(noSqlite)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(noSqlite apps/cli/main.cpp
        src/core/storage/services/PageManager.cpp
        src/core/storage/types/PageHeader.h
)

target_include_directories(noSqlite PRIVATE src)
