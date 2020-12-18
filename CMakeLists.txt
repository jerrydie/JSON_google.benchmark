cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(hse-json LANGUAGES CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
include_directories(src ${CMAKE_CURRENT_BINARY_DIR}/src)

bison_target(parser src/json_parser.ypp src/json_parser.tab.cpp)
flex_target(lexer src/json_lexer.l src/json_lexer.yy.cc)

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/json_model.cpp
                src/json_model.hpp
                src/CustomDriver.hpp
                src/CustomDriver.cpp
                src/CustomScanner.hpp
                ${BISON_parser_OUTPUTS}
                ${FLEX_lexer_OUTPUTS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

find_package(benchmark REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
