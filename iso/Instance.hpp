#pragma once
#include "Cam.hpp"
#include "Color3.hpp"
#include "Vec3.hpp"
#include <string>
#include <vector>

class Instance {
public:
    Instance(const std::string className);
    Instance(const std::string className, Instance* parent);

    // Public methods
    void SetParent(Instance* parent);
    // Lua methods
    const std::vector<Instance*>& GetChildren();
    const std::vector<Instance*>& GetDescendants();
    Instance* FindFirstChild(const std::string name);
    void Destroy();
    bool IsA(const std::string className);

    // Properties on every instance
    const std::string ClassName;
    std::string Name;
    Instance* Parent;

    // Property bitfield for different instance classes
    const uint32_t Properties;
    // Specific properties
    Vec3 Position;
    Vec3 Size = Vec3(1, 1, 1);
    Color3 Color;
    Cam Camera;
    float Distance = 10.0f;
    std::string Code;

    Instance* Index(const std::string name);
    void NewIndex(const std::string key, Instance* parent);

    Instance* child;
    Instance* next;
    Instance* prev;
    bool destroyed = false;

private:
    const uint32_t CalculateProperties();
    void AddDescendants(Instance* root);

    std::vector<Instance*> children;
    std::vector<Instance*> descendants;
};
