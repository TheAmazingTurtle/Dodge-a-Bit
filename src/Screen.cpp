#include "Screen.h"

const int Screen::m_screenPadding = UNIT_SIZE;
const int Screen::m_hudFontSize = 20;
const int Screen::m_hudOffsetY = 40;

void Screen::update() {

}


void Screen::drawHeadupDisplay(int playerLivesLeft, int curScore, int highScore) const {
    const char* scoreText = TextFormat("Score: %d/10", curScore);
    const char* highScoreText = TextFormat("High Score: %d", highScore);

    DrawText(scoreText, (SCREEN_WIDTH - MeasureText(scoreText, m_hudFontSize))/2, m_hudOffsetY, m_hudFontSize, WHITE);
    DrawText(highScoreText, SCREEN_WIDTH - MeasureText(highScoreText, m_hudFontSize) - m_screenPadding, m_hudOffsetY, m_hudFontSize, WHITE);

    // Draw lives
    for (int i = 0; i < playerLivesLeft; i++) {
        const float x = m_screenPadding + i * (30 + 8);
        const float y = m_hudOffsetY;

        Vector2 v1 = { x , y };
        Vector2 v2 = { x - 30 / 2.0f, y + 30 };
        Vector2 v3 = { x + 30 / 2.0f, y + 30 };

        DrawTriangle(v1, v2, v3, PINK); 
    }
}
