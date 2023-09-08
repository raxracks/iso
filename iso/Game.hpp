#pragma once
#include "Instance.hpp"

class Game {
public:
    Game();

    void Run();
    void Stop();

    Instance* game;
    Instance* workspace;
    bool running = false;

private:
    std::vector<Script*> m_Scripts;
};
