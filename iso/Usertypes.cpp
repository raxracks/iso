#include "Usertypes.hpp"
#include "Instance.hpp"

void Usertypes::RegisterUsertypes()
{
    m_State.new_usertype<Instance>(
        "Instance",
        sol::no_constructor,

        "new",
        sol::overload(CreateInstance, CreateInstanceWithParent),

        "Name",
        &Instance::Name,
        "FindFirstChild",
        &Instance::FindFirstChild,
        "GetChildren",
        &Instance::GetChildren,
        "GetDescendants",
        &Instance::GetDescendants,
        "IsA",
        &Instance::IsA,

        sol::meta_function::index,
        &Instance::Index,
        sol::meta_function::new_index,
        &Instance::NewIndex);
}
