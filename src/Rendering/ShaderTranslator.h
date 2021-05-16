//
// Created by fab on 16/05/2021.
//

#ifndef MATERIALEDITOR_SHADERTRANSLATOR_H
#define MATERIALEDITOR_SHADERTRANSLATOR_H

#include <glslang/Public/ShaderLang.h>

class ShaderTranslator {
private:
    glslang::TProgram program;
    glslang::TShader shaderVertex;
    glslang::TShader shaderFrag;

public:
    ShaderTranslator();

};


#endif //MATERIALEDITOR_SHADERTRANSLATOR_H
