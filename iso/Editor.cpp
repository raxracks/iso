#include "Editor.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui_stdlib.h>

void Editor::DrawUI()
{
    ImGui::DockSpaceOverViewport();

    ShowInspector();
    ShowViewport();
    ShowMetrics();
    ImGui::Begin("test");
    {
        if (ImGui::Button("play")) {
            m_Game.Run();
        }
    }
    ImGui::End();
}

void Editor::ShowInspector()
{
    ImGui::Begin("Inspector");
    {
        DrawChildren(m_Game.game);
    }
    ImGui::End();
}

void Editor::ShowViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport");
    {
        ImVec2 size = ImGui::GetContentRegionAvail();
        if ((size.x != m_LastSize.x || size.y != m_LastSize.y) && !ImGui::IsMouseDragging(MouseButton::MOUSE_BUTTON_LEFT)) {
            m_LastSize = size;
            UnloadRenderTexture(m_RenderTexture);
            m_RenderTexture = LoadRenderTexture((int)size.x, (int)size.y);
        }

        rlImGuiImageRenderTexture(&m_RenderTexture);
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void Editor::ShowMetrics()
{
    if (m_ShowMetrics) {
        ImGui::Begin("Metrics", &m_ShowMetrics);
        {
            ImGui::Text("FPS: %d", GetFPS());
            ImGui::Text("Frame time: %f", GetFrameTime());
        }
        ImGui::End();
    }
}

void Editor::ShowProperties()
{
    if (m_SelectedChild != nullptr) {
        ImGui::Begin(("Properties - " + m_SelectedChild->Type + "\"" + m_SelectedChild->Name + "\"").c_str());
        {
            ImGui::Text("Name");
            ImGui::InputText("##name", &m_SelectedChild->Name);

            if (m_SelectedChild->Type == "Part") {
                ImGui::Text("Position");
                ImGui::DragFloat3("##position", &m_SelectedChild->Position.X);
                ImGui::Text("Size");
                ImGui::DragFloat3("##size", &m_SelectedChild->Size.X);
                ImGui::Text("Color");
                ImGui::ColorEdit4("##color", &m_SelectedChild->Color.R);
            }
        }
        ImGui::End();
    }
}

void Editor::DrawChildren(Instance* i)
{
    for (Instance* child : i->children) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_OpenOnDoubleClick
            | ImGuiTreeNodeFlags_SpanAvailWidth;
        if (m_SelectedChild == child)
            flags |= ImGuiTreeNodeFlags_Selected;

        if (ImGui::IsItemClicked())
            m_SelectedChild = child;
        if (ImGui::TreeNodeEx(child, flags, child->Name.c_str())) {
            if (child->children.size() > 0)
                DrawChildren(child);
            ImGui::TreePop();
        }
    }
}
