#pragma once
#include "Instance.hpp"

class Game {
public:
    Game();

    void Run();

    Instance* game;
    Instance* workspace;

private:
};
