#include "Game.h"

Game::Game() : running(true) {}

void Game::Run() {
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Dodge-a-Bit");
    SetTargetFPS(60);

    while (running) {
        float deltaTime = GetFrameTime();

        if (currentState) {
            currentState->Update(*this, deltaTime);
            
            BeginDrawing();
            currentState->Draw(*this);
            EndDrawing();
        }
    }
}

void Game::ChangeState(std::unique_ptr<IGameState> newState) {
    if (currentState) {
        currentState->Exit(*this);
    }

    currentState = std::move(newState);
    currentState->Enter(*this);
}

bool Game::IsRunning() const { return running; }
