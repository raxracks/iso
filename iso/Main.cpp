#include "Instance.hpp"
#include "Usertypes.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui.h>
#include <iostream>
#include <ranges>
#include <raylib.h>
#include <raymath.h>
#include <sol/sol.hpp>
#include <vector>

static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
static int selection_mask = (1 << 2);
int node_clicked = -1;

void DrawChildren(std::shared_ptr<Instance> p)
{
    for (int i = 0; i < p->children.size(); i++) {
        ImGuiTreeNodeFlags node_flags = base_flags;
        const bool is_selected = node_clicked == i;
        if (is_selected)
            node_flags |= ImGuiTreeNodeFlags_Selected;

        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, p->children.at(i)->Name.c_str());
        if (ImGui::IsItemClicked())
            node_clicked = i;
        if (node_open) {
            if (p->children.at(i)->children.size() > 0)
                DrawChildren(p->children.at(i));
            ImGui::TreePop();
        }
    }
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "iso");
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

    auto mat = LoadMaterialDefault();
    mat.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    sol::state lua;
    Usertypes usertypes(lua);
    usertypes.RegisterUsertypes();

    std::shared_ptr<Instance> game = std::make_shared<Instance>("game");
    std::shared_ptr<Instance> workspace = std::make_shared<Instance>("Workspace");
    workspace->SetParent(game);

    for (int i = 0; i < 100; i++) {
        std::shared_ptr<Instance> part = std::make_shared<Instance>("Part");
        part->Name = std::to_string(i);
        std::shared_ptr<Instance> a = std::make_shared<Instance>("a");
        std::make_shared<Instance>("b", a);
        a->SetParent(part);
        part->SetParent(workspace);
    }

    /*lua.open_libraries(sol::lib::base);
    lua.set("game", game);
    lua.set("workspace", workspace);
    lua.safe_script(R"(
for i = 0, 100 do
    local part = Instance.new("Part")
    part.Name = tostring(i)
    part.Parent = workspace

    Instance.new("Part", part)
end
)");*/

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(WHITE);
            BeginMode3D(camera);
            {
                DrawGrid(100, 1);
            }
            EndMode3D();

            rlImGuiBegin();
            {
                ImGui::ShowDemoWindow();

                ImGui::Begin("Inspector");
                {
                    DrawChildren(workspace);
                }
                ImGui::End();
            }
            rlImGuiEnd();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
}
