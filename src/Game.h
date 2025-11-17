#pragma once

#include "GameStates/IGameState.h"
#include "Utils/Config.h"

#include <raylib.h>
#include <memory>

class Game {
public:
    Game();

    void Run();
    void ChangeState(std::unique_ptr<IGameState> newState);
    bool IsRunning() const;
private:
    std::unique_ptr<IGameState> currentState;
    bool running;
};