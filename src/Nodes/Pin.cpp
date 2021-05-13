//
// Created by fab on 01/05/2021.
//

#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include "Pin.h"
#include "Node.h"

Pin::Pin(PinType type, std::string_view name) : name(name), type(type)
{
    imguiID = ++Node::imguiGlobalID;
}

Pin::Pin(PinType type, std::string_view name, std::shared_ptr<Node> &node) : name(name), nodeConnected(node), type(type)
{
    imguiID = ++Node::imguiGlobalID;
}
