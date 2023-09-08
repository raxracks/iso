#pragma once
#include "Color3.hpp"
#include "Script.hpp"
#include "Vec3.hpp"
#include <sol/sol.hpp>
#include <string>
#include <vector>

class Script;

class Instance {
public:
    std::string Name;
    std::string Type;
    Instance* Parent;

    Instance(std::string type);
    Instance(std::string type, Instance* parent);

    Instance* FindFirstChild(std::string name);
    std::vector<Instance*> GetChildren();
    std::vector<Instance*> GetDescendants();
    bool IsA(std::string type);

    Instance* Index(std::string name);
    void NewIndex(std::string key, Instance* parent);

    void SetParent(Instance* parent);

    Vec3 Position;
    Vec3 Size;
    Color3 Color;

    std::string code;

    std::vector<Instance*> children;

private:
    void AddDescendants(Instance* instance, std::vector<Instance*>& descendants);
};

Instance* CreateInstance(std::string type);
Instance* CreateInstanceWithParent(std::string type, Instance* parent);
