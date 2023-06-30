cmake_minimum_required(VERSION 3.8)
project(monitoring VERSION 0.1)

set(__BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(__LIB_DIR ${CMAKE_SOURCE_DIR}/src/libs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${__BUILD_DIR})


# |--------------------------------------------------|
# |                   +++CLIENT+++                   |
# |--------------------------------------------------|
set(__CLIENT_DIR ${CMAKE_SOURCE_DIR}/src/client) 

set(__CLIENT_SRCS 
    ${__CLIENT_DIR}/main.cpp 
    ${__CLIENT_DIR}/login.h 
    ${__CLIENT_DIR}/login.cpp
)

add_executable(client ${__CLIENT_SRCS})



# |--------------------------------------------------|
# |                   +++SERVER+++                   |
# |--------------------------------------------------|
set(__SERVER_DIR ${CMAKE_SOURCE_DIR}/src/server) 

set(__SERVER_SRCS 
    ${__SERVER_DIR}/main.cpp
)

add_executable(server ${__SERVER_SRCS})
