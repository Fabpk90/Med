//
// Created by fab on 13/05/2021.
//

#ifndef MATERIALEDITOR_COLOR_H
#define MATERIALEDITOR_COLOR_H

#include <imgui/imgui.h>
#include "Node.h"

class Color : public Node {
public:
    Color() : Node("Color")
    {
        addInput(PinType::Vec4, "Color");

        addOutput(PinType::Vec4, "");
    };

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


CEREAL_REGISTER_TYPE(Color);

CEREAL_REGISTER_POLYMORPHIC_RELATION(Node, Color);


#endif //MATERIALEDITOR_COLOR_H
