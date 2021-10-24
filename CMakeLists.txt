cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/readline)
<<<<<<< HEAD
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libft/)

FILE(GLOB SRC
        "parsing/*.c"
        )

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
add_executable(minishell ${SRC})
=======
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libft/)

FILE(GLOB SRC
        "sources/builtins/*.c")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")
add_executable(minishell ${SRC} sources/builtins/unset.c)
>>>>>>> 8536a0dbdd562f96e132c889ab79ee2d6eabc25e
target_link_libraries (minishell ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.a)
target_link_libraries (minishell readline)