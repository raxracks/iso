#include "Editor.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui_stdlib.h>

void Editor::Update()
{
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_M)) {
        m_ShowMetrics = true;
    }
}

void Editor::DrawUI()
{
    ImGui::DockSpaceOverViewport();

    ShowInspector();
    ShowViewport();
    ShowMetrics();
    ShowProperties();
    ShowPlayMenu();
}

void Editor::ShowInspector()
{
    ImGui::Begin("Inspector");
    {
        if (ImGui::Button("+")) {
            Instance* instance = new Instance("Part", m_SelectedChild);
        }
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
        ImGui::Begin(("Properties - " + m_SelectedChild->Type + " \"" + m_SelectedChild->Name + "\"###properties").c_str());
        {
            ImGui::Text("Name");
            ImGui::InputText("##name", &m_SelectedChild->Name);
            ImGui::Text("Type");
            ImGui::InputText("##type", &m_SelectedChild->Type);

            if (m_SelectedChild->IsA("Part")) {
                ImGui::Text("Position");
                ImGui::DragFloat3("##position", &m_SelectedChild->Position.X);
                ImGui::Text("Size");
                ImGui::DragFloat3("##size", &m_SelectedChild->Size.X);
                ImGui::Text("Color");
                ImGui::ColorEdit4("##color", &m_SelectedChild->Color.R);
            }

            if (m_SelectedChild->IsA("Script")) {
                ImGui::Begin("Edit");
                {
                    m_TextEditor.Render("##code");
                    auto code = m_TextEditor.GetText();
                    if (code.back() == '\n')
                        code.pop_back();

                    m_SelectedChild->Code = code;
                }
                ImGui::End();
            }
        }
        ImGui::End();
    }
}

void Editor::ShowPlayMenu()
{
    ImGui::Begin("Play");
    {
        if (!m_Game.running) {
            if (ImGui::Button("Run")) {
                m_Game.Run();
            }
        } else {
            if (ImGui::Button("Stop")) {
                m_Game.Stop();
            }
        }
    }
    ImGui::End();
}

void Editor::DrawChildren(Instance* i)
{
    for (Instance* child : i->children) {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_OpenOnDoubleClick
            | ImGuiTreeNodeFlags_SpanAvailWidth;
        if (m_SelectedChild == child)
            flags |= ImGuiTreeNodeFlags_Selected;

        bool isOpen = ImGui::TreeNodeEx(child, flags, child->Name.c_str());
        if (ImGui::IsItemClicked()) {
            m_SelectedChild = child;
            if (m_SelectedChild->IsA("Script"))
                m_TextEditor.SetText(m_SelectedChild->Code);
        }
        if (isOpen) {
            if (child->children.size() > 0)
                DrawChildren(child);
            ImGui::TreePop();
        }
    }
}
