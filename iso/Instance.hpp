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
    std::vector<Instance*> GetDescendantsFilter(std::string filter);
    bool IsA(std::string type);

    Instance* Index(std::string name);
    void NewIndex(std::string key, Instance* parent);

    void SetParent(Instance* parent);

    // Part
    Vec3 Position;
    Vec3 Size;
    Color3 Color;

    // Script
    std::string Code;

    std::vector<Instance*> children;

private:
    void AddDescendants(Instance* instance, std::vector<Instance*>& descendants);
    void AddDescendantsFilter(Instance* instance, std::vector<Instance*>& descendants, std::string filter);
};

Instance* CreateInstance(std::string type);
Instance* CreateInstanceWithParent(std::string type, Instance* parent);
