cmake_minimum_required (VERSION 3.0)  # 필수 정보

project (SWING)  # 필수 정보

set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/AST)

#file(GLOB_RECURSE FILESYSTEM "${PROJECT_SOURCE_DIR}/lib/filesystem/*.cpp" "${PROJECT_SOURCE_DIR}/lib/filesystem/*.hpp")

#add_library(filesystem STATIC ${FILESYSTEM})
#install(TARGETS filesystem DESTINATION lib/filesystem)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h")
add_executable(swing ${SOURCES})
