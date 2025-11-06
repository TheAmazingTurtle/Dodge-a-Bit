#include "StartScreen.hpp"
#include "config.hpp"


StartScreen::StartScreen() {}
StartScreen::~StartScreen() {}

void StartScreen::update(float deltaTime) {

}

void StartScreen::draw() const{
    DrawText(TextFormat("DODGE-A-BIT"), (SCREEN_WIDTH - MeasureText("DODGE-A-BIT", 50)) / 2, SCREEN_HEIGHT / 3, 50, WHITE);

    DrawText(TextFormat("Press ENTER to play!"), (SCREEN_WIDTH - MeasureText("Press ENTER to play!", 30)) / 2, SCREEN_HEIGHT / 3 * 2, 30, WHITE);
    // DrawText(TextFormat("Music : ON"), 4.5, 8, 20, WHITE);
    // DrawText(TextFormat("Sounds : ON"), 4.5, 8, 20, WHITE);
    // DrawText(TextFormat("Instructions"), 4.5, 8, 20, WHITE);
    // DrawText(TextFormat("Exit"), 4.5, 8, 20, WHITE);
}

