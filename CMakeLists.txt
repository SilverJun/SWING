cmake_minimum_required (VERSION 3.0)  # 필수 정보

project (SWING)  # 필수 정보

set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(swing ${SOURCES})
