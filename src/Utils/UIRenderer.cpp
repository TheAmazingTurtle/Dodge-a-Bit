#include "UIRenderer.h"

void UIRenderer::drawHeadupDisplay(int playerLivesLeft, int score, int highScore) {
    static const int screenPadding = Config::UNIT_SIZE;
    static const int hudFontSize = 20;
    static const int hudOffsetY = 40;

    const char* scoreText = TextFormat("Score: %d", score);
    const char* highScoreText = TextFormat("High Score: %d", highScore);

    DrawText(scoreText, (Config::SCREEN_WIDTH - MeasureText(scoreText, hudFontSize))/2, hudOffsetY, hudFontSize, WHITE);
    DrawText(highScoreText, Config::SCREEN_WIDTH - MeasureText(highScoreText, hudFontSize) - screenPadding, hudOffsetY, hudFontSize, WHITE);

    // Draw lives
    for (int i = 0; i < playerLivesLeft; i++) {
        const float x = screenPadding + i * (30 + 8);
        const float y = hudOffsetY;

        Vector2 v1 = { x , y };
        Vector2 v2 = { x - 30 / 2.0f, y + 30 };
        Vector2 v3 = { x + 30 / 2.0f, y + 30 };

        DrawTriangle(v1, v2, v3, PINK); 
    }
}