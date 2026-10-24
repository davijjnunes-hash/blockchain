cmake_minimum_required(VERSION 3.16)

project(blockchain
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(blockchain
src/main.c
src/block.c
)

find_package(OpenSSL REQUIRED)

target_include_directories(blockchain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(blockchain PRIVATE OpenSSL::Crypto)
