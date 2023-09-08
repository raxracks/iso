#pragma once
#include "Instance.hpp"
#include <sol/sol.hpp>

class Instance;

class Script {
public:
    Script(Instance* game, Instance* workspace, std::string code);

private:
    sol::state m_State;
};
