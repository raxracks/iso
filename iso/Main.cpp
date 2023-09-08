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
    Instance* part = new Instance("Part", game.workspace);
    Instance* script = new Instance("Script", part);
    script->Code = R"(local part = script.Parent
part.Size = Vector3.new(math.random(1, 10), math.random(1, 10), math.random(1, 10))
part.Position = Vector3.new(math.random(-10, 10), math.random(-10, 10), math.random(-10, 10))

while wait() do
    part.Color = Color3.new(math.random(), math.random(), math.random())
end
)";

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
            BeginMode3D(camera);
            {
                DrawGrid(100, 1);
                for (Instance* child : game.workspace->GetDescendantsFilter("Part")) {
                    DrawCube(child->Position, child->Size.X, child->Size.Y, child->Size.Z, child->Color);
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
