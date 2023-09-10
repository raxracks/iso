#pragma once
#include "Cam.hpp"
#include "Color3.hpp"
#include "Vec3.hpp"
#include <string>
#include <vector>

class Instance {
public:
    Instance(std::string type);
    Instance(std::string type, Instance* parent);

    void SetParent(Instance* parent);
    std::vector<Instance*> GetChildren();
    std::vector<Instance*> GetDescendants();
    Instance* FindFirstChild(std::string name);
    void Destroy();
    bool IsA(std::string type);

    Instance* Parent;

    std::string Type;
    std::string Name;
    Vec3 Position;
    Vec3 Size;
    Color3 Color;
    Cam Camera;
    float Distance;
    std::string Code;

    Instance* Index(std::string name);
    void NewIndex(std::string key, Instance* parent);

    Instance* child;
    Instance* next;
    Instance* prev;
    bool destroyed = false;

private:
    void AddDescendants(Instance* root, std::vector<Instance*>& descendants);
    Instance* m_Game;
};
