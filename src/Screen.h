#pragma once
#include <raylib.h>

#include "config.h"

class Screen {
public:
    ~Screen() = default;

    void update();
    void drawStartScreen() const;
    void drawBackground() const;
    void drawHeadupDisplay(int playerLivesLeft, int curScore, int highScore) const;

private:
    static const int m_screenPadding;
    static const int m_hudFontSize;
    static const int m_hudOffsetY;

};