#include "Game.hpp"

Game::Game()
{
    game = new Instance("game");
    workspace = new Instance("Workspace", game);
}

void Game::Run()
{
    for (Instance* child : workspace->children) {
        if (child->IsA("Script")) {
            Script(game, workspace, child->code);
        }
    }
}
