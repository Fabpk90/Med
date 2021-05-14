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

void Node::drawPin()
{
    for (auto& pin : pinsInput)
    {
       pin->draw();
    }

    for (auto& pin : pinsOutput)
    {
       pin->draw();
    }
}

void Node::addInput(PinType type, std::string_view name, std::shared_ptr<Node> &node)
{
    pinsInput.emplace_back(std::move(std::make_unique<Pin>(PinIO::Input, type, name, node)));
}

void Node::addInput(PinType type, std::string_view name)
{
    pinsInput.emplace_back(std::move(std::make_unique<Pin>(PinIO::Input, type, name)));
}

void Node::addOutput(PinType type, std::string_view name, std::shared_ptr<Node> &node)
{
    pinsOutput.emplace_back(std::move(std::make_unique<Pin>(PinIO::Output, type, name, node)));
}

void Node::addOutput(PinType type, std::string_view name)
{
    pinsOutput.emplace_back(std::move(std::make_unique<Pin>(PinIO::Output, type, name)));
}
