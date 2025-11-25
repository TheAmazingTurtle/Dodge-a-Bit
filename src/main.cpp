#include <raylib.h>

#include "Game.h"

int main() {
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Dodge-a-Bit");
    SetTargetFPS(60);

    Game game;
    game.Run();
}
