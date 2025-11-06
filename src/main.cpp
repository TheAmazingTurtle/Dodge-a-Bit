#include "config.hpp"
#include "Screen.hpp"
#include "GameScreen.hpp"
#include "StartScreen.hpp"

#include <memory>
#include <raylib.h>

unsigned char testByte = 0b10101010;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    std::unique_ptr<Screen> activeScreen = std::make_unique<StartScreen>();

    // game running
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        activeScreen->update(deltaTime);

        BeginDrawing();
        activeScreen->draw();
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            activeScreen = std::make_unique<GameScreen>();
        }
    }
    return 0;
}