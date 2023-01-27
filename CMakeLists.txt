cmake_minimum_required(VERSION 3.18)
project(PoskoSemestralnaPraca C)

set(CMAKE_C_STANDARD 99)

add_executable(PoskoSemestralnaPraca
        main.c
        k_s_server.c
        k_s_client.c
        k_s_definitions.h
        k_s_definitions.c
        k_s_server.h
        k_s_client.h
        kocka.c
        kocka.h
        panacik.c
        panacik.h
        farbaHraca.h
        stavPanacika.h
        policko.c
        policko.h
        hrac.c
        hrac.h
        Obrazok.c
        Obrazok.h
        hraciaPlocha.c
        hraciaPlocha.h
        hraClovece.c
        hraClovece.h farbaHraca.c)

