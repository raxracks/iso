#include "Instance.hpp"

Instance::Instance(std::string type)
{
    Type = type;
    Name = type;
}

Instance::Instance(std::string type, std::shared_ptr<Instance> parent)
{
    Type = type;
    Name = type;
    SetParent(parent);
}

std::shared_ptr<Instance> Instance::FindFirstChild(std::string name)
{
    auto it = std::ranges::find_if(children, [&](auto& child) {
        return child->Name == name;
    });

    if (it != children.end())
        return *it;
    else
        return nullptr;
}

std::vector<std::shared_ptr<Instance>> Instance::GetChildren()
{
    return children;
}

void Instance::SetParent(std::shared_ptr<Instance> parent)
{
    Parent = parent;
    Parent->children.push_back(std::make_unique<Instance>(*this));
}

bool Instance::IsA(std::string type)
{
    return Type == type;
}

std::shared_ptr<Instance> Instance::Index(std::string name)
{
    if (name == "Parent")
        return Parent;

    return FindFirstChild(name);
}

void Instance::NewIndex(std::string key, std::shared_ptr<Instance> parent)
{
    if (key == "Parent")
        SetParent(parent);
}
