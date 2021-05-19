cmake_minimum_required(VERSION 3.19)
project(MaterialEditor)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/external)

link_directories(${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_subdirectory(src)

install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION bin)