cmake_minimum_required(VERSION 3.18)
project(PoskoSemestralnaPraca C)

set(CMAKE_C_STANDARD 99)

add_executable(PoskoSemestralnaPraca main.c
        k_s_server.c
        k_s_client.c
        k_s_definitions.h
        k_s_definitions.c
        k_s_server.h
        k_s_client.h
        Clovece/kocka.c
        Clovece/kocka.h
        Clovece/panacik.c
        Clovece/panacik.h
        Clovece/farbaHraca.h
        Clovece/stavPanacika.h
        Clovece/policko.c
        Clovece/policko.h
        Clovece/hrac.c
        Clovece/hrac.h
        Clovece/Obrazok.c
        Clovece/Obrazok.h
        Clovece/hraciaPlocha.c
        Clovece/hraciaPlocha.h
        Clovece/hraClovece.c
        Clovece/hraClovece.h)

