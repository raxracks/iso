#include "Renderer.hpp"
#include "rlImGui/rlImGui.h"
#include <raylib.h>

class RaylibSurfaceTexture : public SurfaceTexture {
public:
    RaylibSurfaceTexture(int width, int height)
    {
        texture = LoadRenderTexture(width, height);
    }
    void Begin() override;
    void End() override;
    void ImGuiImage() override;
    void Resize(int width, int height) override;

private:
    RenderTexture texture;
};

class RaylibRenderer : public Renderer {
    void Initialize() override;
    void Begin() override;
    void End() override;
    void ImGuiBegin() override;
    void ImGuiEnd() override;
    void ImGuiSurfaceTextureImage(SurfaceTexture* surfaceTexture) override;
    void Shutdown() override;
    SurfaceTexture* CreateSurfaceTexture(int width, int height) override;
};
