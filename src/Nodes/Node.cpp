//
// Created by fab on 01/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Node.h"

int Node::imguiGlobalID = 0;

Node::Node(std::string_view name) : name(name)
{
    imguiID = ++imguiGlobalID;
    ImNodes::SetNodeScreenSpacePos(imguiID, position);
}

Node::Node(std::string_view name, ImVec2 position)
        : name(name), position(position)
{
    imguiID = ++imguiGlobalID;
    ImNodes::SetNodeScreenSpacePos(imguiID, position);
}

Node::Node(std::string_view name, float x, float y)
        : name(name), position(x, y)
{
    imguiID = ++imguiGlobalID;
    ImNodes::SetNodeScreenSpacePos(imguiID, position);
}

void Node::addInput(std::unique_ptr<Pin> pin)
{
    pinsInput.push_back(std::move(pin));
}

void Node::addOutput(std::unique_ptr<Pin> pin)
{
    pinsOutput.push_back(std::move(pin));
}

void Node::drawPin()
{
    for (auto& pin : pinsInput)
    {
        ImNodes::BeginInputAttribute(pin->getID());
            ImGui::Text("%s", pin->getName().c_str());
        ImNodes::EndInputAttribute();
    }

    for (auto& pin : pinsOutput)
    {
        ImNodes::BeginOutputAttribute(pin->getID());
            const float label_width = ImGui::CalcTextSize(name.c_str()).x;
            ImGui::Indent(80.0f + label_width);
            ImGui::Text("%s", pin->getName().c_str());
        ImNodes::EndOutputAttribute();
    }
}
