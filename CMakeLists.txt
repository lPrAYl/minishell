cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)
include_directories(~/.brew/opt/readline/include)
#include_directories(/usr/include/readline/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft/)

FILE(GLOB SRC
        "parsing/*.c"
        "sources/*.c"
        "sources/builtins/*.c"
        "sources/pipex/*.c"
        "sources/utils/*.c"
        )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
add_executable(minishell ${SRC} )
target_link_libraries (minishell ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.a)
target_link_libraries (minishell readline)