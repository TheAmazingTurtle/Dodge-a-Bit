#include "GameOverScreen.h"
#include <string>

GameOverScreen::GameOverScreen() 
    :   tryAgainButton("Try Again", { 0,0 }, { 200, 60 }),
        exitButton("Exit", { 0,0 }, { 200, 60 }),
        waveReached(1)
{
    float centerX = (GetScreenWidth() - 200) / 2;
    float startY = 500;
    float spacing = 80;

    Button* buttons[] = { &tryAgainButton, &exitButton };

    for (int i = 0; i < 2; i++) {
        buttons[i]-> SetPosition ({ centerX, startY + spacing * i });
    }

}
GameOverScreen::~GameOverScreen() {}

void GameOverScreen::Draw() const{
    DrawGameOverText();
    DrawButtons();
}

void GameOverScreen::Update() {
    gameOverAction = GameOverScreenAction::None;
    Vector2 mousePos = GetMousePosition();
    bool isClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (tryAgainButton.IsPressed(mousePos, isClicked))  gameOverAction = GameOverScreenAction::TryAgain;
    else if (exitButton.IsPressed(mousePos, isClicked)) gameOverAction = GameOverScreenAction::Exit;
}

bool GameOverScreen::IsTryAgainPressed() const{return gameOverAction == GameOverScreenAction::TryAgain;}
bool GameOverScreen::IsExitPressed() const{return gameOverAction == GameOverScreenAction::Exit;}

void GameOverScreen::DrawGameOverText() const{
    const char* gameOverText = "Oops! You got zapped!";
    int gameOverFontSize = 50;
    int gameOverTextWidth = MeasureText(gameOverText, gameOverFontSize);

    // const char* highestWaveText = TextFormat("Wave Reached: %d", waveReached);
    // int highestWaveFontSize = 20;
    // int highestWaveTextWidth = MeasureText(highestWaveReachedText, highestWaveFontSize);

    const char* waveReachedText = TextFormat("Wave Reached: %d", waveReached);
    int waveFontSize = 30;
    int waveTextWidth = MeasureText(waveReachedText, waveFontSize);

    DrawText(gameOverText, (GetScreenWidth() - gameOverTextWidth) / 2, 150, gameOverFontSize, RED);
    // DrawText(TextFormat("Highest Wave: %d", recordedHighestWave), baseX * 8.5, baseY + 8, 20, WHITE);
    DrawText(waveReachedText,(GetScreenWidth() - waveTextWidth) / 2, 300, waveFontSize, WHITE);
}

void GameOverScreen::DrawButtons() const{
    tryAgainButton.Draw();
    exitButton.Draw();
}

void GameOverScreen::SetWaveReached(int waveNumber) {
    waveReached = waveNumber;
}