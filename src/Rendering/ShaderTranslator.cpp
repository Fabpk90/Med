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

    main = builder.makeEntryPoint("main");

    block = &builder.makeNewBlock();

    auto instruction = std::make_unique<spv::Instruction>(spv::OpIAdd);
    instruction->addIdOperand(a);
    instruction->addIdOperand(b);

    block->addInstruction(std::move(instruction));

    main->addBlock(block);

    std::vector<unsigned int> dumps;
    builder.dump(dumps);
}
