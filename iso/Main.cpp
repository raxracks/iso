#include "Editor.hpp"
#include "Game.hpp"
#include "Instance.hpp"
#include "Script.hpp"
#include "Usertypes.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui.h>
#include <iostream>
#include <ranges>
#include <raylib.h>
#include <raymath.h>
#include <sol/sol.hpp>
#include <vector>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "iso");
    SetExitKey(KEY_NULL);
    rlImGuiSetup(true);

    Camera3D camera {};
    camera.fovy = 30.0f;
    camera.position = Vector3 {
        30,
        30,
        30,
    };
    camera.target = Vector3 { 0, 0, 0 };
    camera.up = Vector3 { 0, 1, 0 };
    camera.projection = CAMERA_PERSPECTIVE;

    Game game;
    Instance* script = new Instance("Script", game.workspace);
    script->code = R"(
for i = 0, 10000 do
    local part = Instance.new("Part", workspace)
    part.Name = tostring(i)
    part.Position = Vector3.new(math.random(-100, 100),
            math.random(0, 10),
            math.random(-100, 100))
    part.Size = Vector3.new(math.random(1, 5), math.random(1, 5), math.random(1, 5))
    part.Color = Color3.new(math.random(), math.random(), math.random())
end)";

    RenderTexture viewport = LoadRenderTexture(600, 400);
    Editor editor(game, viewport);

    while (!WindowShouldClose()) {
        BeginTextureMode(viewport);
        {
            ClearBackground(WHITE);
            BeginMode3D(camera);
            {
                DrawGrid(100, 1);
                for (Instance* child : game.workspace->children) {
                    if (child->Type == "Part") {
                        DrawCube(child->Position, child->Size.X, child->Size.Y, child->Size.Z, child->Color);
                    }
                }
            }
            EndMode3D();
        }
        EndTextureMode();

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

    rlImGuiShutdown();
    CloseWindow();
}
