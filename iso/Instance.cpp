#include "Instance.hpp"

Instance::Instance(std::string type)
{
    Type = type;
    Name = type;
}

Instance::Instance(std::string type, Instance* parent)
{
    Type = type;
    Name = type;
    SetParent(parent);
}

Instance* Instance::FindFirstChild(std::string name)
{
    auto it = std::ranges::find_if(children, [&](Instance child) {
        return child.Name == name;
    });

    if (it != children.end())
        return &(*it);
    else
        return nullptr;
}

std::vector<Instance> Instance::GetChildren()
{
    return children;
}

void Instance::SetParent(Instance* parent)
{
    Parent = parent;
    Parent->children.push_back(*this);
}

bool Instance::IsA(std::string type)
{
    return Type == type;
}

Instance* Instance::Index(std::string name)
{
    if (name == "Parent")
        return Parent;

    return FindFirstChild(name);
}

void Instance::NewIndex(std::string key, Instance* parent)
{
    if (key == "Parent")
        SetParent(parent);
}
