#include "Usertypes.hpp"
#include "Instance.hpp"

void Usertypes::RegisterUsertypes()
{
    m_State.new_usertype<Instance>(
        "Instance",
        sol::constructors<Instance(std::string), Instance(std::string, std::shared_ptr<Instance> parent)>(),

        "Name",
        &Instance::Name,
        "FindFirstChild",
        &Instance::FindFirstChild,
        /*"GetChildren",
        &Instance::GetChildren,*/
        "IsA",
        &Instance::IsA,

        sol::meta_function::index,
        &Instance::Index,
        sol::meta_function::new_index,
        &Instance::NewIndex);
}
