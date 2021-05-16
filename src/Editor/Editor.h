//
// Created by fab on 11/05/2021.
//

#ifndef MATERIALEDITOR_EDITOR_H
#define MATERIALEDITOR_EDITOR_H

#include <vector>
#include <numeric>

#include <cereal/types/memory.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>
#include "../Rendering/Framebuffer.h"
#include "../Rendering/Vbo.h"
#include "../Rendering/ShaderTranslator.h"


class Node;

class Editor{
private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::pair<int, int>> links;

    float windowSizeX;
    float windowSizeY;

    Framebuffer fb;
    Vbo vboQuad;
    ShaderTranslator translator;

public:
    Editor() = delete;
    Editor(float x, float y);

    Editor(const Editor& cpy) = delete;

    static Editor* instance;

    void draw();

    void render();

    Framebuffer& getFB() { return fb; }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( nodes, links); // serialize things by passing them to the archive
    }

    void addNode(std::shared_ptr<Node>&& node)
    {
        nodes.push_back(node);
    }

    void addLink(int startID, int endID)
    {
        links.emplace_back(startID, endID);
    }

    void removeLink(int startID, int endID);
    void removeLink(int index)
    {
        links.erase(links.begin() + index);
    }

    bool removeNodeByID(int ID);

    std::shared_ptr<Node> getNodeByID(int nodeID);

    std::shared_ptr<Node> getNodeByIndex(int nodeIndex)
    {
        return nodes[nodeIndex];
    }

    std::pair<float, float> getWindowSize() { return {windowSizeX, windowSizeY}; }

    void reset();
};


#endif //MATERIALEDITOR_EDITOR_H
