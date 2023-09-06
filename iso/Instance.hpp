#pragma once
#include <sol/sol.hpp>
#include <string>
#include <vector>

class Instance {
public:
    std::string Name;
    std::string Type;
    Instance* Parent;

    Instance(std::string type);
    Instance(std::string type, Instance* parent);

    Instance* FindFirstChild(std::string name);
    std::vector<Instance> GetChildren();
    bool IsA(std::string type);

    Instance* Index(std::string name);
    void NewIndex(std::string key, Instance* parent);

    void SetParent(Instance* parent);

    std::vector<Instance> children;
};
