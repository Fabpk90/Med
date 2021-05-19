#include <glad/glad.c>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <iostream>
#include <imnodes/imnodes.h>

#include <cereal/archives/json.hpp>

#include "Nodes/Node.h"
#include "Nodes/Math/Add.h"
#include "Editor/Editor.h"
#include "Nodes/Color.h"
#include <vector>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

int main() {
    glfwInit();
    ImGui::CreateContext();
    ImNodes::CreateContext();

   // ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    auto* window = glfwCreateWindow(1280, 720, "Material Editor", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    Editor editor = Editor(1280, 720);

    //check if settings of the editor are present

    std::ifstream f("settings.txt");
    if(f.good())
    {
        f.close();
        ImGui::LoadIniSettingsFromDisk("settings.txt");
        ImNodes::LoadCurrentEditorStateFromIniFile("settingsEditor.txt");
    }

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE)
        {
            ImGui::SaveIniSettingsToDisk("settings.txt");
            ImNodes::SaveCurrentEditorStateToIniFile("settingsEditor.txt");
            glfwSetWindowShouldClose(window, true);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        editor.render();

        ImGui::NewFrame();

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

       // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::Begin("node editor", nullptr, window_flags);

        ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            ImGui::Image((ImTextureID)(editor.getFB().getColorTexture()), ImVec2(256, 256));
        ImGui::End();

        if(ImGui::Button("New"))
        {
            editor.reset();
        }
        ImGui::SameLine();
        if(ImGui::Button("Save"))
        {
            std::cout << "Saving.." << std::endl;
            std::ofstream s("test.txt");
            cereal::JSONOutputArchive oarchive(s); // Create an output archive

            oarchive(CEREAL_NVP(editor)); // Write the data to the archive

            std::cout << "Saved !" << std::endl;
        }
        ImGui::SameLine();
        if(ImGui::Button("Load"))
        {
            std::cout << "Loading.." << std::endl;
            std::ifstream s("test.txt");
            cereal::JSONInputArchive iarchive(s); // Create an output archive

            editor.reset();
            iarchive(CEREAL_NVP(editor)); // Write the data to the archive

            std::cout << "Loaded !" << std::endl;
        }

        ImNodes::BeginNodeEditor();

        const bool open_popup = //ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)
                                /*&&*/ ImNodes::IsEditorHovered()
                                && (glfwGetKey(window, GLFW_KEY_SPACE) || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT));

        if (open_popup)
        {
            /*ImGui::OpenPopup("Context Menu");
            ImGui::BeginPopup("Context Menu");
            static ImGuiTextFilter filter;

            filter.Draw();
            const char* lines[] = { "Add"};
            for (auto & line : lines)
                if (filter.PassFilter(line))*/
                    ImGui::OpenPopup("add node");
        }

        if (ImGui::BeginPopup("add node"))
        {
            const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

            if (ImGui::MenuItem("add"))
            {
                std::shared_ptr<Add> node = std::make_shared<Add>();

                node->setPosition(click_pos);
                ImNodes::SetNodeScreenSpacePos(node->getID(), click_pos);

                editor.addNode(std::move(node));
            }

            if (ImGui::MenuItem("color"))
            {
                std::shared_ptr<Color> node = std::make_shared<Color>();

                node->setPosition(click_pos);
                ImNodes::SetNodeScreenSpacePos(node->getID(), click_pos);

                editor.addNode(std::move(node));
            }

            ImGui::EndPopup();
        }

       /* if(open_popup)
            ImGui::EndPopup();*/

        editor.draw();

        ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);
        ImNodes::EndNodeEditor();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        int start_attr, end_attr;
        if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
        {
            editor.addLink(start_attr, end_attr);
        }

        const int num_selected = ImNodes::NumSelectedLinks();
        if (num_selected > 0 && glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_TRUE)
        {
            static std::vector<int> selected_links;
            selected_links.resize(static_cast<size_t>(num_selected));
            ImNodes::GetSelectedLinks(selected_links.data());
            for (const int edge_id : selected_links)
            {
                editor.removeLink(edge_id);
            }

            ImNodes::ClearLinkSelection();
        }

        int nodeID;
        if(ImNodes::IsNodeHovered(&nodeID))
        {
            auto node = editor.getNodeByID(nodeID);
            node->setPosition(ImNodes::GetNodeScreenSpacePos(nodeID));
        }
    }

    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
