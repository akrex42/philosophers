cmake_minimum_required(VERSION 3.20)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

add_executable(philosophers main.c philo_main.c)
