#pragma once
#include "Game.hpp"
#include "Instance.hpp"
#include <imgui.h>
#include <raylib.h>

class Editor {
public:
    Editor(Game& game, RenderTexture& renderTexture)
        : m_Game(game)
        , m_RenderTexture(renderTexture)
        , m_SelectedChild(nullptr)
        , m_LastSize(0, 0)
        , m_ShowMetrics(false)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    };
    void DrawUI();

private:
    Game& m_Game;
    Instance* m_SelectedChild;
    RenderTexture& m_RenderTexture;
    ImVec2 m_LastSize;
    bool m_ShowMetrics;

    void ShowInspector();
    void ShowViewport();
    void ShowMetrics();
    void ShowProperties();

    void DrawChildren(Instance* i);
};
