#include "GameOverState.h"

GameOverState::GameOverState(int finalScore, int highScore) : playerFinalScore(finalScore), recordedHighScore (highScore), 
    mainMenuButton("Main Menu", { 0,0 }, { 200, 60 }),
    tryAgainButton("Try Again", { 0,0 }, { 200, 60 }),
    exitButton("Exit", { 0,0 }, { 200, 60 }) {

        float centerX = (Config::SCREEN_WIDTH - 200) / 2;
        float startY = 500;
        float spacing = 80;

        Button* buttons[] = { &mainMenuButton, &tryAgainButton, &exitButton };

        for (int i = 0; i < 3; i++) {
            buttons[i]-> SetPosition ({ centerX, startY + spacing * i });
    }
    }

void GameOverState::Enter(Game& game) {

}

void GameOverState::Exit(Game& game) {

}

void GameOverState::Update(Game& game, float deltaTime) {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

    switch (GetButtonAction(GetMousePosition())) {
        case ButtonAction::MainMenu:
            game.ChangeState(std::make_unique<StartState>());
            break;
        case ButtonAction::TryAgain:
            game.ChangeState(std::make_unique<GameplayState>());
            break;
        case ButtonAction::Exit:
            game.EndGame();
            break;
        default:
            break;
    }
}

void GameOverState::Draw(Game& game) const {
    ClearBackground(BLACK);

    const char* gameOverText = "Oops! You got zapped!";
    int gameOverFontSize = 50;
    int gameOverTextWidth = MeasureText(gameOverText, gameOverFontSize);

    // const char* highestWaveText = TextFormat("Wave Reached: %d", waveReached);
    // int highestWaveFontSize = 20;
    // int highestWaveTextWidth = MeasureText(highestWaveReachedText, highestWaveFontSize);

    const char* highScoreText = TextFormat("High Score : %d", recordedHighScore);
    const char* playerScoreText = TextFormat("Your Score : %d", playerFinalScore);
    int highScoreFontSize = 20;
    int playerScoreFontSize = 30;
    int highScoreTextWidth = MeasureText(highScoreText, highScoreFontSize);
    int playerScoreTextWidth = MeasureText(playerScoreText, playerScoreFontSize);

    DrawText(gameOverText, (GetScreenWidth() - gameOverTextWidth) / 2, 150, gameOverFontSize, RED);
    // DrawText(TextFormat("Highest Wave: %d", recordedHighestWave), baseX * 8.5, baseY + 8, 20, WHITE);
    DrawText(playerScoreText,(GetScreenWidth() - playerScoreTextWidth) / 2, 300, playerScoreFontSize, WHITE);
    DrawText(highScoreText,(GetScreenWidth() - highScoreTextWidth) / 2, 350, highScoreFontSize, GREEN);

    mainMenuButton.Draw();
    tryAgainButton.Draw();
    exitButton.Draw();
}

std::string GameOverState::GetName() const {
    return "Game Over";
}

GameOverState::ButtonAction GameOverState::GetButtonAction(Vector2 mousePosition) const {
    if (mainMenuButton.IsPressed(mousePosition, true)) return ButtonAction::MainMenu;
    if (tryAgainButton.IsPressed(mousePosition, true)) return ButtonAction::TryAgain;
    if (exitButton.IsPressed(mousePosition, true)) return ButtonAction::Exit;
    return ButtonAction::None;
}
