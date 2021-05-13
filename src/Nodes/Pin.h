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

    int imguiID;

public:
    Pin() = default;
    Pin(PinType type, std::string_view name);
    Pin(PinType type, std::string_view name, std::shared_ptr<Node>& node);

    void setNode(std::shared_ptr<Node> node) { nodeConnected = node; }

    const PinType& getType() { return type; }
    const PinIO& getIoType() { return pinIo; }
    const std::string& getName() { return name; }
    int getID() { return imguiID; }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( imguiID, name, pinIo, type, nodeConnected); // serialize things by passing them to the archive
    }

};


#endif //MATERIALEDITOR_PIN_H
