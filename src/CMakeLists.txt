file(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
file(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)
file(GLOB_RECURSE IMGUI_SOURCES ../external/imgui/*.cpp)

add_executable(MaterialEditor ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_HEADERS} ../external/imnodes/imnodes.cpp)

target_link_libraries(MaterialEditor glfw3)