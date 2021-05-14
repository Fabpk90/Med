//
// Created by fab on 01/05/2021.
//

#ifndef MATERIALEDITOR_PIN_H
#define MATERIALEDITOR_PIN_H

#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>

#include <string>
#include <memory>

class Node;

enum class PinIO : char
{
    Input,
    Output
};

enum class PinType : char
{
    Float,
    Vec2,
    Vec3,
    Vec4,
    Mat,
    Void
};

class Pin {
protected:
    std::string name;
    std::shared_ptr<Node> nodeConnected;

    PinIO pinIo;
    PinType type;

    ImVec4 data = ImVec4(0, 0, 0, 1);

    int imguiID;

public:
    Pin() = default;
    Pin(PinIO io, PinType type, std::string_view name);
    Pin(PinIO io, PinType type, std::string_view name, std::shared_ptr<Node>& node);

    void setNode(std::shared_ptr<Node> node) { nodeConnected = node; }

    void draw();
    void drawType();

    const PinType& getType() { return type; }
    const PinIO& getIoType() { return pinIo; }
    const std::string& getName() { return name; }
    int getID() { return imguiID; }

    const ImVec4& getData() { return data; }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( imguiID, name, pinIo, type, data.x, data.y, data.z, data.w, nodeConnected);
    }

};


#endif //MATERIALEDITOR_PIN_H
