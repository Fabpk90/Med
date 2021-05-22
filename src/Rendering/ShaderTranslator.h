//
// Created by fab on 16/05/2021.
//

#ifndef MATERIALEDITOR_SHADERTRANSLATOR_H
#define MATERIALEDITOR_SHADERTRANSLATOR_H


#include <glslang/SPIRV/Logger.h>
#include <glslang/SPIRV/SpvBuilder.h>
#include <glslang/Public/ShaderLang.h>

class ShaderTranslator {
private:
    glslang::TProgram program;

    spv::SpvBuildLogger buildLogger;
    spv::Builder builder;

public:
    ShaderTranslator();

    spv::Function* main;
    spv::Block* block;
};


#endif //MATERIALEDITOR_SHADERTRANSLATOR_H
