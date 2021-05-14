//
// Created by fab on 01/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Pin.h"
#include "Node.h"

Pin::Pin(PinIO io, PinType type, std::string_view name) : pinIo(io), name(name), type(type)
{
    imguiID = ++Node::imguiGlobalID;
}

Pin::Pin(PinIO io, PinType type, std::string_view name, std::shared_ptr<Node> &node) : pinIo(io), name(name), nodeConnected(node), type(type)
{
    imguiID = ++Node::imguiGlobalID;
}

void Pin::draw()
{
    if(pinIo == PinIO::Input)
    {
        ImNodes::BeginInputAttribute(imguiID);
            ImGui::Text("%s", name.c_str());
            drawType();
        ImNodes::EndInputAttribute();
    }
    else
    {
        ImNodes::BeginOutputAttribute(imguiID);
            const float label_width = ImGui::CalcTextSize(name.c_str()).x;
            ImGui::Indent(80.0f + label_width);
            ImGui::Text("%s", name.c_str());
        ImNodes::EndOutputAttribute();
    }
}

void Pin::drawType() 
{
    switch (type) {
        case PinType::Float:
            ImGui::DragFloat("", &data.x);
            break;
        case PinType::Vec2:
            ImGui::DragFloat2("", &data.x);
            break;
        case PinType::Vec3:
            ImGui::DragFloat3("", &data.x);
            break;
        case PinType::Vec4:
            ImGui::DragFloat4("", &data.x);
            break;
        case PinType::Mat:
            break;
        case PinType::Void:
            break;
    }
}
