cmake_minimum_required(VERSION 3.26)
project(sairchEngine)

set(CMAKE_CXX_STANDARD 14)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(sairchEngine main.cpp
        include/jsonConv.h
        src/jsonConv.cpp)

include_directories(sairchEngine PUBLIC {CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(sairchEngine PRIVATE nlohmann_json::nlohmann_json)