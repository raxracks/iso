#include "RaylibRenderer.hpp"
#include <iostream>

void RaylibRenderer::Initialize()
{
    SetExitKey(KEY_NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "iso");
    SetTargetFPS(60);
    MaximizeWindow();
    rlImGuiSetup(true);

    std::cout << "initialized raylib" << std::endl;
}

void RaylibRenderer::Begin()
{
    BeginDrawing();
}

void RaylibRenderer::End()
{
    EndDrawing();
}

void RaylibRenderer::ImGuiBegin()
{
    rlImGuiBegin();
}

void RaylibRenderer::ImGuiEnd()
{
    rlImGuiEnd();
}

void RaylibRenderer::ImGuiSurfaceTextureImage(SurfaceTexture* surfaceTexture)
{
    surfaceTexture->ImGuiImage();
}

void RaylibRenderer::Shutdown()
{
    rlImGuiShutdown();
    CloseWindow();
}

SurfaceTexture* RaylibRenderer::CreateSurfaceTexture(int width, int height)
{
    return new RaylibSurfaceTexture(width, height);
}

void RaylibSurfaceTexture::Begin()
{
    BeginTextureMode(texture);
}

void RaylibSurfaceTexture::End()
{
    EndTextureMode();
}

void RaylibSurfaceTexture::ImGuiImage()
{
    rlImGuiImageRenderTexture(&texture);
}

void RaylibSurfaceTexture::Resize(int width, int height)
{
    UnloadRenderTexture(texture);
    texture = LoadRenderTexture(width, height);
}
