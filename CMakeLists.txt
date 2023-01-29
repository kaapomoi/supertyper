cmake_minimum_required(VERSION 3.20)

project(supertyper VERSION 0.0.1
    LANGUAGES CXX C
)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC core)


