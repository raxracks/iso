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
    auto it = std::ranges::find_if(children, [&](auto& child) {
        return child->Name == name;
    });

    if (it != children.end())
        return *it;
    else
        return nullptr;
}

std::vector<Instance*> Instance::GetChildren()
{
    return children;
}

std::vector<Instance*> Instance::GetDescendants()
{
    std::vector<Instance*> descendants;
    AddDescendants(this, descendants);

    return descendants;
}

std::vector<Instance*> Instance::GetDescendantsFilter(std::string filter)
{
    std::vector<Instance*> descendants;
    AddDescendantsFilter(this, descendants, filter);

    return descendants;
}

void Instance::SetParent(Instance* parent)
{
    Parent = parent;
    Parent->children.push_back(this);
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

void Instance::AddDescendants(Instance* instance, std::vector<Instance*>& descendants)
{
    for (Instance* child : instance->children) {
        descendants.push_back(child);
        if (child->children.size() > 0)
            AddDescendants(child, descendants);
    }
}

void Instance::AddDescendantsFilter(Instance* instance, std::vector<Instance*>& descendants, std::string filter)
{
    for (Instance* child : instance->children) {
        if (child->IsA(filter))
            descendants.push_back(child);
        if (child->children.size() > 0)
            AddDescendantsFilter(child, descendants, filter);
    }
}

Instance* CreateInstance(std::string type)
{
    return new Instance(type);
}

Instance* CreateInstanceWithParent(std::string type, Instance* parent)
{
    return new Instance(type, parent);
}
