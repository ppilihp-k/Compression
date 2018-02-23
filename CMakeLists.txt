cmake_minimum_required(VERSION 3.0)
project(Datastructures CXX C)

set(CMAKE_CXX_STANDARD 11)
#-fopt-info-vec-missed
#-DNDEBUG
set(CMAKE_CXX_FLAGS " -pthread -O3 -std=c++11 -funroll-loops -mavx -march=native -ftree-vectorize -ftree-vectorizer-verbose=2")
#set(CMAKE_CXX_FLAGS "-DNDEBUG -std=c++11 -msse4.2 -mavx -mavx2 -march=native -ftree-vectorize -fopt-info-vec-missed")

#include directories
include_directories(include)

add_subdirectory(source )

#add_library(datastructures STATIC ${SRC})
target_link_libraries(datastructures)
