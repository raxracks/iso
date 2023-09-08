#include "Script.hpp"
#include "Usertypes.hpp"

Script::Script(Instance* game, Instance* workspace, std::string code)
{
    Usertypes(m_State).RegisterUsertypes();
    m_State.open_libraries(sol::lib::base, sol::lib::math);
    m_State.set("game", game);
    m_State.set("workspace", workspace);
    m_State.safe_script(code);
}
