//
// Created by fab on 13/05/2021.
//

#ifndef MATERIALEDITOR_MASTERNODE_H
#define MATERIALEDITOR_MASTERNODE_H

#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>

#include "Node.h"

class MasterNode : public Node {
public:

    MasterNode() : Node("Master Node"){};

    MasterNode(ImVec2 position) : Node("Master Node", position)
    {
        addInput(PinType::Void ,"Color");
    }

    void draw() override;

    void evaluate() override;

    void drawPin() override;

    void connectInput(int index, std::shared_ptr<Node> nodeConnected) override;

    void connectOutput(int index, std::shared_ptr<Node> nodeConnected) override;

    template<class Archive>
    void serialize(Archive & archive)
    {
        Node::serialize(archive);
    }
};

CEREAL_REGISTER_TYPE(MasterNode);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Node, MasterNode);

#endif //MATERIALEDITOR_MASTERNODE_H
