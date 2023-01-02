cmake_minimum_required(VERSION 3.18)
project(PoskoSemestralnaPraca C)

set(CMAKE_C_STANDARD 99)


set(MAIN_FUNCTION main)
add_executable(client k_s_client.c k_s_definitions.h k_s_definitions.c)
target_compile_definitions(client PRIVATE "MAIN_FUNCTION=main_client")

add_executable(server k_s_server.c k_s_definitions.h k_s_definitions.c)
target_compile_definitions(server PRIVATE "MAIN_FUNCTION=main_server")
