cmake_minimum_required(VERSION 3.16)

#
# SpadesX
#

project(SpadesX)

#
# Add third party libraries
#

add_subdirectory(Extern)

#
# Add main target
#
add_compile_options(-Wall -Wextra)
add_executable(server "")

target_link_libraries(server
    PRIVATE
        enet
        util
        vxl
        m
        json-c
        pthread
)

add_subdirectory(Source)
