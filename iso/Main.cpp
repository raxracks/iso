#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

#include "Instance.hpp"
#include "Usertypes.hpp"
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
    struct nk_context* ctx = InitNuklear(20);

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

    auto mat = LoadMaterialDefault();
    mat.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    sol::state lua;
    Usertypes usertypes(lua);
    usertypes.RegisterUsertypes();

    Instance game("game");
    Instance workspace("Workspace");
    workspace.SetParent(&game);

    lua.open_libraries(sol::lib::base);
    lua.set("game", &game);
    lua.set("workspace", &workspace);
    lua.safe_script(R"(
for i = 0, 100 do
    local part = Instance.new("Part")
    part.Name = tostring(i)
    part.Parent = workspace
end
)");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateNuklear(ctx);

        if (nk_begin(ctx, "Nuklear", nk_rect(100, 100, 220, 220),
                NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
            if (nk_button_label(ctx, "Button")) {
                // Button was clicked!
            }
        }
        nk_end(ctx);

        BeginDrawing();
        {
            ClearBackground(WHITE);
            BeginMode3D(camera);
            {
                DrawGrid(100, 1);
            }
            EndMode3D();

            DrawNuklear(ctx);
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    CloseWindow();
}
