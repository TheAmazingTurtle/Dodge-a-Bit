#include <raylib.h>

#include "Game.h"
#include "GameStates/StartState.h"

int main() {
    Game game;
    game.ChangeState(std::make_unique<StartState>());
    game.Run();
}
