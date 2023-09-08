#pragma once
#include "Game.hpp"
#include "ImGuiColorTextEdit/TextEditor.h"
#include "Instance.hpp"
#include <imgui.h>

class Editor {
public:
    Editor(Game& game, RenderTexture& renderTexture);

    void Update();
    void DrawUI();

private:
    Game& m_Game;
    Instance* m_SelectedChild;
    RenderTexture& m_RenderTexture;
    ImVec2 m_LastSize;
    TextEditor m_TextEditor;
    ImFont* m_MainFont;
    ImFont* m_FiraFont;
    bool m_ShowMetrics;

    void ShowInspector();
    void ShowViewport();
    void ShowMetrics();
    void ShowProperties();
    void ShowPlayMenu();

    void DrawChildren(Instance* i);
};
