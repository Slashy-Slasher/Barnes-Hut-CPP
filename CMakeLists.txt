cmake_minimum_required(VERSION 3.12)

project(Barnes-Hut)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Don't modify CMAKE_PREFIX_PATH manually; use toolchain file instead
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/include")


# Use raylib from vcpkg (via toolchain)

 find_package(raylib CONFIG REQUIRED)

add_executable(Barnes-Hut 
"Barnes-Hut/Barnes-Hut.cpp"
)

target_link_libraries(Barnes-Hut PRIVATE raylib)
