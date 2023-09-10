#pragma once

class SurfaceTexture {
public:
    virtual void Begin() {};
    virtual void End() {};
    virtual void ImGuiImage() {};
    virtual void Resize(int width, int height) {};
};

class Renderer {
public:
    virtual void Initialize() {};
    virtual void Begin() {};
    virtual void End() {};
    virtual void ImGuiBegin() {};
    virtual void ImGuiEnd() {};
    virtual void ImGuiSurfaceTextureImage(SurfaceTexture* surfaceTexture) {};
    virtual void Shutdown() {};
    virtual SurfaceTexture* CreateSurfaceTexture(int width, int height) { return nullptr; };
};
