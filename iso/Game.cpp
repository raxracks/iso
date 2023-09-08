#include "Game.hpp"

Game::Game()
{
    game = new Instance("game");
    workspace = new Instance("Workspace", game);
}

void Game::Run()
{
    for (Instance* child : workspace->GetDescendantsFilter("Script")) {
        Script* script = new Script(game, workspace, child, child->Code);
        m_Scripts.push_back(script);
    }

    running = true;
}

void Game::Stop()
{
    for (Script* s : m_Scripts) {
        s->~Script();
    }

    running = false;
}
