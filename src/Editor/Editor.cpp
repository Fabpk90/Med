//
// Created by fab on 11/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Editor.h"
#include "../Nodes/Node.h"
#include "../Nodes/MasterNode.h"

Editor* Editor::instance = nullptr;

Editor::Editor(float x, float y) : windowSizeX(x), windowSizeY(y), fb(x, y, true, true)
, vboQuad(2, 6)
{
    addNode(std::make_unique<MasterNode>(ImVec2(x / 2, y / 2)));

    vboQuad.setElementDescription(0, Vbo::Element(3)); // position
    vboQuad.setElementDescription(1, Vbo::Element(2)); // uv

    vboQuad.createCPUSide();

    //projection space
    vboQuad.setElementData(0, 0, 1, 0, 0);
    vboQuad.setElementData(1, 0, 1, 0);
    vboQuad.setElementData(0, 0, 1, 0, 0);

    instance = this;
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

void Editor::render()
{
    fb.bind();
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vboQuad.bind();

    fb.unBind();
}

void Editor::reset()
{
    nodes.clear();
    links.clear();

    //reset shader
}
