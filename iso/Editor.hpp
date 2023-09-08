#pragma once
#include "Game.hpp"
#include "ImGuiColorTextEdit/TextEditor.h"
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
        m_TextEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
    };

    void Update();
    void DrawUI();

private:
    Game& m_Game;
    Instance* m_SelectedChild;
    RenderTexture& m_RenderTexture;
    ImVec2 m_LastSize;
    TextEditor m_TextEditor;
    bool m_ShowMetrics;

    void ShowInspector();
    void ShowViewport();
    void ShowMetrics();
    void ShowProperties();
    void ShowPlayMenu();

    void DrawChildren(Instance* i);
};
