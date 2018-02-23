include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include/include")

file(GLOB libFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SRC ${libFiles})
#set(SRC array.cpp)

add_library(datastructures STATIC ${SRC})

