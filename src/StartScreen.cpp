#include "StartScreen.h"
#include <string>

StartScreen::StartScreen() {}

StartScreen::~StartScreen() {}

void StartScreen::Draw() const{
    // Draw texts
    DrawGameTitle();
    DrawPlayText();
    DrawMusicOnText();
    DrawSoundOnText();
    DrawInstructionsText();
    DrawExitText();
}

void StartScreen::DrawGameTitle() const {
    DrawText(TextFormat("DODGE-A-BIT"), 4.5, 8, 20, WHITE);
}

void StartScreen::DrawPlayText() const {
    DrawText(TextFormat("Play"), 4.5, 8, 20, WHITE);
}

void StartScreen::DrawMusicOnText() const {
    DrawText(TextFormat("Music : ON"), 4.5, 8, 20, WHITE);
}

void StartScreen::DrawSoundOnText() const {
    DrawText(TextFormat("Sounds : ON"), 4.5, 8, 20, WHITE);
}

void StartScreen::DrawInstructionsText() const {
    DrawText(TextFormat("Instructions"), 4.5, 8, 20, WHITE);
}

void StartScreen::DrawExitText() const {
    DrawText(TextFormat("Exit"), 4.5, 8, 20, WHITE);
}
