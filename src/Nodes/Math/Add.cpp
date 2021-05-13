//
// Created by fab on 01/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Add.h"

void Add::draw() {
    ImNodes::BeginNode(imguiID);
        ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(name.c_str());
        ImNodes::EndNodeTitleBar();
            drawPin();
        ImGui::Dummy(ImVec2(80.0f, 45.0f));
    ImNodes::EndNode();
}

void Add::evaluate()
{
    if(pinsInput.size() > 2)
    {

    }
}

Add::Add() : Node("Add")
{
    addInput(std::move(std::make_unique<Pin>(PinType::Float, "A")));
    addInput(std::move(std::make_unique<Pin>(PinType::Float, "B")));

    addOutput(std::move(std::make_unique<Pin>(PinType::Float, "C")));
}

void Add::connectInput(int index, std::shared_ptr<Node> nodeConnected)
{
    pinsInput[index]->setNode(nodeConnected);
}

void Add::connectOutput(int index, std::shared_ptr<Node> nodeConnected)
{
    pinsOutput[index]->setNode(nodeConnected);
}
