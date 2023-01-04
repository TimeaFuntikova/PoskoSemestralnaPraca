cmake_minimum_required(VERSION 3.18)
project(PoskoSemestralnaPraca C)

set(CMAKE_C_STANDARD 99)

add_executable(PoskoSemestralnaPraca main.c k_s_server.c k_s_client.c k_s_definitions.h k_s_definitions.c k_s_server.h k_s_client.h)

