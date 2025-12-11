cmake_minimum_required(VERSION 3.10)
project(k C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        main.c
        src/logic.c
        src/file.c
        src/ui.c
        src/init.c
)

add_executable(k ${SOURCES})

target_include_directories(k PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if (WIN32)
    target_compile_definitions(k PRIVATE
            _CRT_SECURE_NO_WARNINGS
            PLATFORM_WINDOWS
    )
else()
    target_compile_definitions(k PRIVATE
            PLATFORM_LINUX
    )
endif()
