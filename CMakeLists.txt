cmake_minimum_required (VERSION 3.22)

project(API_RESTFUL)

file(MAKE_DIRECTORY bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SERVER_SOURCE src/server.c)
set(CLIENT_SOURCE src/client.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wextra -Wconversion -std=gnu11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(server ${SERVER_SOURCE})
add_executable(client ${CLIENT_SOURCE})

target_link_libraries(server
    -lulfius
    -ljansson
    -lorcania
    -lm
    -lpthread
)