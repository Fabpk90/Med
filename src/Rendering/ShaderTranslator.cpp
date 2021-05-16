//
// Created by fab on 16/05/2021.
//

#include "ShaderTranslator.h"

ShaderTranslator::ShaderTranslator() : shaderVertex(EShLangVertex), shaderFrag(EShLangFragment)
{
    shaderVertex.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
    shaderFrag.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);

}
