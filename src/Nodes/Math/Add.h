//
// Created by fab on 01/05/2021.
//

#ifndef MATERIALEDITOR_ADD_H
#define MATERIALEDITOR_ADD_H

#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>

#include "../Node.h"

class Add : public Node {

public:
    Add();

    void draw() override;

    void evaluate() override;

    void connectInput(int index, std::shared_ptr<Node>) override;

    void connectOutput(int index, std::shared_ptr<Node> nodeConnected) override;

    template<class Archive>
    void serialize(Archive & archive)
    {
       Node::serialize(archive);
    }
};

CEREAL_REGISTER_TYPE(Add);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Node, Add);

#endif //MATERIALEDITOR_ADD_H