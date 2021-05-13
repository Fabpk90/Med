//
// Created by fab on 13/05/2021.
//

#include <imgui/imgui.h>
#include "MasterNode.h"

void MasterNode::draw()
{
    ImNodes::BeginNode(imguiID);
        ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(name.c_str());
        ImNodes::EndNodeTitleBar();
            drawPin();
            ImGui::Dummy(ImVec2(80.0f, 45.0f));
    ImNodes::EndNode();
}

void MasterNode::evaluate()
{

}

void MasterNode::drawPin()
{
    Node::drawPin();
}

void MasterNode::connectInput(int index, std::shared_ptr<Node> nodeConnected)
{

}

void MasterNode::connectOutput(int index, std::shared_ptr<Node> nodeConnected)
{

}
