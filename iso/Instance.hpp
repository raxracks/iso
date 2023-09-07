#pragma once
#include <sol/sol.hpp>
#include <string>
#include <vector>

class Instance {
public:
    std::string Name;
    std::string Type;
    std::shared_ptr<Instance> Parent;

    Instance(std::string type);
    Instance(std::string type, std::shared_ptr<Instance> parent);

    std::shared_ptr<Instance> FindFirstChild(std::string name);
    std::vector<std::shared_ptr<Instance>> GetChildren();
    bool IsA(std::string type);

    std::shared_ptr<Instance> Index(std::string name);
    void NewIndex(std::string key, std::shared_ptr<Instance> parent);

    void SetParent(std::shared_ptr<Instance> parent);

    std::vector<std::shared_ptr<Instance>> children;
};
