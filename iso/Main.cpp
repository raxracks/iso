#include "Editor.hpp"
#include "Game.hpp"
#include "Instance.hpp"
#include "Script.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui.h>
#include <raylib.h>
#include <vector>

int main()
{
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "iso");
    SetTargetFPS(60);
    MaximizeWindow();
    rlImGuiSetup(true);

    Game game;
    RenderTexture viewport = LoadRenderTexture(600, 400);
    Editor editor(game, viewport);

    bool editing = true;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E)) {
            editing = !editing;
        }

        if (editing) {
            editor.Update();
            BeginTextureMode(viewport);
        } else
            BeginDrawing();
        {
            ClearBackground(WHITE);
            BeginMode3D(game.camera->Camera);
            {
                DrawGrid(100, 1);
                for (Instance* child : game.workspace->GetDescendants()) {
                    if (child) {
                        if (child->destroyed) {
                            if (child->prev != nullptr) {
                                child->prev->next = child->next;
                            }
                            if (child->next != nullptr) {
                                child->next->prev = child->prev;
                            }
                            if (child->Parent->child == child) {
                                child->Parent->child = child->next;
                            }

                            if (editor.m_SelectedChild == child)
                                editor.m_SelectedChild = nullptr;

                            delete child;
                        } else {
                            if (child->IsA("Part")) {
                                DrawCube(child->Position, child->Size.X, child->Size.Y, child->Size.Z, child->Color);
                            }
                        }
                    }
                }
            }
            EndMode3D();
        }

        if (editing)
            EndTextureMode();
        else
            EndDrawing();

        if (editing) {
            BeginDrawing();
            {
                ClearBackground(BLACK);

                rlImGuiBegin();
                {
                    editor.DrawUI();
                }
                rlImGuiEnd();
            }
            EndDrawing();
        }
    }

    rlImGuiShutdown();
    CloseWindow();
}
