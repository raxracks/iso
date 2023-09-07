#include "Instance.hpp"
#include "Usertypes.hpp"
#include "rlImGui/rlImGui.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <iostream>
#include <ranges>
#include <raylib.h>
#include <raymath.h>
#include <sol/sol.hpp>
#include <vector>

static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
static int selection_mask = (1 << 2);
Instance* selected;
int i = 0;

void DrawChildren(Instance* p)
{
    for (Instance* child : p->children) {
        ImGuiTreeNodeFlags node_flags = base_flags;
        const bool is_selected = selected == child;
        if (is_selected)
            node_flags |= ImGuiTreeNodeFlags_Selected;

        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)(i++), node_flags, child->Name.c_str());
        if (ImGui::IsItemClicked())
            selected = child;
        if (node_open) {
            if (child->children.size() > 0)
                DrawChildren(child);
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

    Instance* game = new Instance("game");
    Instance* workspace = new Instance("Workspace");
    workspace->SetParent(game);

    lua.open_libraries(sol::lib::base);
    lua.set("game", game);
    lua.set("workspace", workspace);
    lua.safe_script(R"(
for i = 0, 100 do
    local part = Instance.new("Part", workspace)
    part.Name = tostring(i)

    local child = Instance.new("Part", part)
    child.Name = "child of " .. tostring(i)

    local childchild = Instance.new("Part", child)
    childchild.Name = "child of child of " .. tostring(i)
end
)");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    RenderTexture viewport = LoadRenderTexture(600, 400);
    ImVec2 lastSize(600, 400);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        i = 0;

        BeginTextureMode(viewport);
        {
            ClearBackground(WHITE);
            BeginMode3D(camera);
            {
                DrawGrid(100, 1);
            }
            EndMode3D();
        }
        EndTextureMode();

        BeginDrawing();
        {
            ClearBackground(BLACK);

            rlImGuiBegin();
            {
                ImGui::DockSpaceOverViewport();

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                ImGui::Begin("Viewport");
                {
                    ImVec2 size = ImGui::GetContentRegionAvail();
                    if ((size.x != lastSize.x || size.y != lastSize.y) && !ImGui::IsMouseDragging(MouseButton::MOUSE_BUTTON_LEFT)) {
                        lastSize = size;
                        UnloadRenderTexture(viewport);
                        viewport = LoadRenderTexture(size.x, size.y);
                    }

                    rlImGuiImageRenderTexture(&viewport);
                }
                ImGui::End();
                ImGui::PopStyleVar();

                ImGui::Begin("Inspector");
                {
                    DrawChildren(workspace);
                }
                ImGui::End();

                if (selected != nullptr) {
                    ImGui::Begin(("Properties - " + selected->Type).c_str());
                    {
                        ImGui::Text("Name");
                        ImGui::InputText("##name", &selected->Name);
                    }
                    ImGui::End();
                }
            }
            rlImGuiEnd();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
}
