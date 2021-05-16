file(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
file(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)
file(GLOB_RECURSE IMGUI_SOURCES ../external/imgui/*.cpp)

add_executable(MaterialEditor ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_HEADERS} ../external/imnodes/imnodes.cpp)

IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(GLSLANGLIBS glslangd HLSLd OSDependentd OGLCompilerd SPIRVd MachineIndependentd GenericCodeGend)
else()
    set(GLSLANGLIBS glslang HLSL OSDependent OGLCompiler SPIRV MachineIndependent GenericCodeGen)
endif()

target_link_libraries(MaterialEditor glfw3 ${GLSLANGLIBS})