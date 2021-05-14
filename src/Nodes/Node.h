//
// Created by fab on 01/05/2021.
//

#ifndef MATERIALEDITOR_NODE_H
#define MATERIALEDITOR_NODE_H

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>

#include <imnodes/imnodes.h>

#include <vector>
#include <memory>
#include <string>
#include "Pin.h"

class Node {
public:
    static int imguiGlobalID;

protected:
    int imguiID;
    std::vector<std::unique_ptr<Pin>> pinsInput;
    std::vector<std::unique_ptr<Pin>> pinsOutput;
    std::string name;

    ImVec2 position;

public:
    Node(std::string_view name, ImVec2 position);
    Node(std::string_view name, float x, float y);
    Node(std::string_view name);

    virtual ~Node() = default;

    virtual void draw() = 0;
    virtual void evaluate() = 0;

    virtual void drawPin();

    virtual void connectInput(int index, std::shared_ptr<Node> nodeConnected) = 0;
    virtual void connectOutput(int index, std::shared_ptr<Node> nodeConnected) = 0;

    void addInput(PinType type, std::string_view name, std::shared_ptr<Node>& node);
    void addInput(PinType type, std::string_view name);

    void addOutput(PinType type, std::string_view name, std::shared_ptr<Node>& node);
    void addOutput(PinType type, std::string_view name);

    [[nodiscard]] int getID() const { return imguiID; }

    void setPosition(ImVec2 _position) { position = _position; }
    const ImVec2& getPosition() { return position; }

    template<class Archive>
    void serialize(Archive & archive)
    {
        position = ImNodes::GetNodeScreenSpacePos(imguiID);
        archive( imguiID, pinsInput, pinsOutput, position.x, position.y); // serialize things by passing them to the archive
    }

};

#endif //MATERIALEDITOR_NODE_H
