cmake_minimum_required(VERSION 3.16)
project(PageManager)

set(CMAKE_CXX_STANDARD 14)
set(PAGE_MANAGER_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${PAGE_MANAGER_SRC_INCLUDE_DIR})
add_executable(PageManager main.cpp src/include/replacer.h src/include/define.h src/replacer/lru_replacer.cpp src/include/lru_replacer.h src/replacer/opt_replacer.cpp src/include/opt_replacer.h src/replacer/fifo_replacer.cpp src/include/fifo_replacer.h src/replacer/replacer.cpp)
add_subdirectory(src)
