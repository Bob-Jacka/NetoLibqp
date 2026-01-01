cmake_minimum_required(VERSION 3.31)
project(NetoLibpq)

set(CMAKE_CXX_STANDARD 23)

add_executable(NetoLibpq
        main.cpp
        core/entities/DbController.hpp
        core/entities/DbController.cpp
        core/entities/SQLexception.hpp

        libio.cppm
)

add_subdirectory(core/dependencies/libpqxx-7.10.4 build-pqxx)
target_link_libraries(NetoLibpq PRIVATE pqxx)

target_sources(NetoLibpq
        PUBLIC
        FILE_SET all_my_modules TYPE CXX_MODULES FILES
        libio.cppm
)