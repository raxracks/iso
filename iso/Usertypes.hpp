#pragma once
#include <sol/sol.hpp>

class Usertypes {
public:
    Usertypes(sol::state& state)
        : m_State(state) {};

    void RegisterUsertypes();

private:
    sol::state& m_State;
};
