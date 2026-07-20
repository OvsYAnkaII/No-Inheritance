cmake_minimum_required(VERSION 4.0)
project(VTable_original)

set(CMAKE_CXX_STANDARD 14)

include_directories("../../VTable original — копия")

add_executable(VTable_original
        driving_licence.h
        identity_document.h
        international_driving_licence.h
        main.cpp
        main_original.cpp
        passport.h
        travel_pack.h)
