//
// Created by fab on 11/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Editor.h"
#include "../Nodes/Node.h"
#include "../Nodes/MasterNode.h"

Editor::Editor()
{
    addNode(std::make_unique<MasterNode>(ImVec2(0, 0)));
}

void Editor::draw()
{
    for (auto& node : nodes)
    {
        node->draw();
        //ImNodes::SetNodeScreenSpacePos(node->getID(), node->getPosition());
    }

    for (int i = 0; i < links.size(); ++i)
    {
        const std::pair<int, int> p = links[i];
        // in this case, we just use the array index of the link
        // as the unique identifier
        ImNodes::Link(i, p.first, p.second);
    }
}

bool Editor::removeNodeByID(int ID)
{
    return false;
}

void Editor::removeLink(int startID, int endID)
{
    int index = -1;
    std::pair<int, int> pairToTest = {startID, endID};
    for(int i = 0; i < links.size(); ++i)
    {
        if(links[i] == pairToTest)
        {
            index = i;
            break;
        }
    }

    if(index != -1)
        links.erase(links.begin() + index);
}

std::shared_ptr<Node> Editor::getNodeByID(int nodeID)
{
    for (auto& node : nodes)
    {
        if(node->getID() == nodeID)
            return node;
    }

    return nullptr;
}


