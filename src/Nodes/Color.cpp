//
// Created by fab on 13/05/2021.
//

#include "Color.h"

void Color::draw()
{
    ImNodes::BeginNode(imguiID);
        ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(name.c_str());
        ImNodes::EndNodeTitleBar();
            drawPin();
            ImGui::Image(nullptr, ImVec2(80.0f, 45.0f), ImVec2(0, 0), ImVec2(1, 1), pinsInput[0]->getData());
    ImNodes::EndNode();
}

void Color::evaluate() {

}

void Color::drawPin() {
    Node::drawPin();
}

void Color::connectInput(int index, std::shared_ptr<Node> nodeConnected) {

}

void Color::connectOutput(int index, std::shared_ptr<Node> nodeConnected)
{

}
