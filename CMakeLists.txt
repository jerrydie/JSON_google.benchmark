cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(hse-json LANGUAGES CXX)

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/json_model.cpp
                src/json_model.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
