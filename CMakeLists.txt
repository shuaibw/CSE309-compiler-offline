cmake_minimum_required(VERSION 3.22)
project(symbolTableOffline)

set(CMAKE_CXX_STANDARD 14)

add_executable(symbolTableOffline
        main.cpp SymbolInfo.h ScopeTable.h SymbolTable.h)