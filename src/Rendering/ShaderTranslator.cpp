//
// Created by fab on 16/05/2021.
//

#include <fstream>
#include "ShaderTranslator.h"

ShaderTranslator::ShaderTranslator() : buildLogger() , builder(spv::SpvVersion::Spv_1_4, 0, &buildLogger)
{
    auto a = builder.makeInt16Constant(5);
    auto b = builder.makeFloat16Constant(5);

    std::vector<spv::Id>ids = {a,b};

    auto add = builder.createOp(spv::OpIAdd, builder.makeFloatType(16), ids);

    std::vector<unsigned int> dumps;
    builder.dump(dumps);
}
