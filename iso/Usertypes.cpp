#include "Usertypes.hpp"
#include "Color3.hpp"
#include "Instance.hpp"
#include "Vec3.hpp"

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

        "Position",
        &Instance::Position,
        "Size",
        &Instance::Size,
        "Color",
        &Instance::Color,

        sol::meta_function::index,
        &Instance::Index,
        sol::meta_function::new_index,
        &Instance::NewIndex);

    m_State.new_usertype<Vec3>("Vector3",
        sol::constructors<Vec3(), Vec3(float, float, float)>(),

        "X",
        &Vec3::X,
        "Y",
        &Vec3::Y,
        "Z",
        &Vec3::Z);

    m_State.new_usertype<Color3>("Color3",
        sol::constructors<Color3(),
            Color3(float, float, float),
            Color3(float, float, float, float)>(),

        "R",
        &Color3::R,
        "G",
        &Color3::G,
        "B",
        &Color3::B,
        "A",
        &Color3::A);
}
