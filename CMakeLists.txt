cmake_minimum_required (VERSION 3.0)  # 필수 정보

project (SWING)  # 필수 정보

set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/AST)
include_directories(${PROJECT_SOURCE_DIR}/src/Type)
include_directories(${PROJECT_SOURCE_DIR}/src/Debugger)

#file(GLOB_RECURSE FILESYSTEM "${PROJECT_SOURCE_DIR}/lib/filesystem/*.cpp" "${PROJECT_SOURCE_DIR}/lib/filesystem/*.hpp")

#add_library(filesystem STATIC ${FILESYSTEM})
#install(TARGETS filesystem DESTINATION lib/filesystem)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE SRC_AST "${PROJECT_SOURCE_DIR}/src/AST/*.cpp" "${PROJECT_SOURCE_DIR}/src/AST/*.h")
file(GLOB_RECURSE SRC_DEBUGGER "${PROJECT_SOURCE_DIR}/src/Debugger/*.cpp" "${PROJECT_SOURCE_DIR}/src/Debugger/*.h")
file(GLOB_RECURSE SRC_TYPE "${PROJECT_SOURCE_DIR}/src/Type/*.cpp" "${PROJECT_SOURCE_DIR}/src/Type/*.h")

add_executable(swing ${SOURCES} ${SRC_AST} ${SRC_DEBUGGER} ${SRC_TYPE})

source_group("AST" FILES ${SRC_AST})
source_group("Debugger" FILES ${SRC_DEBUGGER})
source_group("Type" FILES ${SRC_TYPE})

