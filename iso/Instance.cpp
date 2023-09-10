#include "Instance.hpp"
#include <iostream>

Instance::Instance(std::string type)
    : Camera(Cam(Position, Distance))
{
    Type = type;
    Name = type;
}

Instance::Instance(std::string type, Instance* parent)
    : Camera(Cam(Position, Distance))
{
    Type = type;
    Name = type;
    SetParent(parent);
}

void Instance::SetParent(Instance* parent)
{
    if (Parent != nullptr) {
        if (next != nullptr) {
            next->prev = prev;
        }
        if (prev != nullptr) {
            prev->next = next;
        }

        if (Parent->child == this) {
            Parent->child = next;
        }
    }
    Parent = parent;
    Instance* current = Parent->child;
    next = nullptr;
    if (current == nullptr) {
        Parent->child = this;
        prev = nullptr;
    } else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = this;
        prev = current;
    }
}

std::vector<Instance*> Instance::GetChildren()
{
    std::vector<Instance*> children;
    Instance* current = child;
    while (current != nullptr) {
        children.push_back(current);
        current = current->next;
    }

    return children;
}

std::vector<Instance*> Instance::GetDescendants()
{
    std::vector<Instance*> descendants;
    AddDescendants(this, descendants);
    return descendants;
}

Instance* Instance::FindFirstChild(std::string name)
{
    std::vector<Instance*> children = GetChildren();

    auto it = std::ranges::find_if(children, [&](Instance* child) {
        return child->Name == name;
    });

    if (it != children.end())
        return *it;
    else
        return nullptr;
}

void Instance::Destroy()
{
    destroyed = true;

    Instance* c = child;
    while (c != nullptr) {
        c->Destroy();
        c = c->next;
    }
}

bool Instance::IsA(std::string type)
{
    return Type == type;
}

void Instance::AddDescendants(Instance* root, std::vector<Instance*>& descendants)
{
    for (Instance* child : root->GetChildren()) {
        descendants.push_back(child);
        AddDescendants(child, descendants);
    }
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

uint32_t Instance::GetProperties()
{
    if (Type == "Part") {
        return Properties::Position | Properties::Size | Properties::Color;
    } else if (Type == "Script") {
        return Properties::Code;
    } else if (Type == "Camera") {
        return Properties::Position | Properties::Distance;
    }

    return 0;
}
