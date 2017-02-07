cmake_minimum_required (VERSION 3.0)  # 필수 정보

project (SWING)  # 필수 정보

include_directories(${PROJECT_SOURCE_DIR}/llvm)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(swing ${SOURCES})
