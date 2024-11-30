cmake_minimum_required(VERSION 3.20.0)
project(ArcEncryptor VERSION 0.1.0)

set(CXX_STANDARD 17)
include(CPack)

# file(GLOB_RECURSE sources CMAKE_CONFIGURE_DEPENDS "src/**/*.hpp" "src/**/*.h" "src/**/*.cpp" "src/**/*.c")

include_directories(
    src/**
)

add_library(arc-encryptor-lib SHARED "src/arc_encryptor.cpp" "src/arc_encryptor.hpp" "src/arc_utils.hpp")