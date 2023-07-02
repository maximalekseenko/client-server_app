cmake_minimum_required(VERSION 3.8)
project(monitoring VERSION 0.1)

set(__BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(__LIB_DIR ${CMAKE_SOURCE_DIR}/src/libs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BUILD_DIR})



# |--------------------------------------------------|
# |                 +++LIBRARIES+++                  |
# |--------------------------------------------------|


find_package (SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


# |--------------------------------------------------|
# |                   +++CLIENT+++                   |
# |--------------------------------------------------|


set(__CLIENT_DIR ${CMAKE_SOURCE_DIR}/src/client) 

set(__CLIENT_SRCS 
    ${__CLIENT_DIR}/main.cpp 
    ${__CLIENT_DIR}/login.cpp
    ${__CLIENT_DIR}/login.h 
    ${__CLIENT_DIR}/connection.cpp
    ${__CLIENT_DIR}/connection.h
)

add_executable(client ${__CLIENT_SRCS})


# |--------------------------------------------------|
# |                   +++SERVER+++                   |
# |--------------------------------------------------|


set(__SERVER_DIR ${CMAKE_SOURCE_DIR}/src/server) 

set(__SERVER_SRCS 
    ${__SERVER_DIR}/main.cpp
    ${__SERVER_DIR}/connection.cpp
    ${__SERVER_DIR}/connection.h
    ${__SERVER_DIR}/threading.cpp
    ${__SERVER_DIR}/threading.h
    ${__SERVER_DIR}/data.cpp
    ${__SERVER_DIR}/data.h
    ${__SERVER_DIR}/window.cpp
    ${__SERVER_DIR}/window.h
    ${__SERVER_DIR}/windows.h
)

add_executable(server ${__SERVER_SRCS})
target_link_libraries (server ${SQLite3_LIBRARIES})
target_link_libraries (server ${CURSES_LIBRARIES})

