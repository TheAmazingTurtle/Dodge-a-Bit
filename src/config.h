#pragma once

const int UNIT_SIZE = 64;
const int NUM_TURRETS = 8;
const int SCREEN_WIDTH = UNIT_SIZE * 10;
const int SCREEN_HEIGHT = UNIT_SIZE * 15;

enum class GameState {
    StartScreen, 
    GameOngoing,
    GameOver,
    GameWin
};

enum class Direction {
    Left, Right
};

enum class BitwiseOperator {
    NOT,
    AND, OR, XOR,
    SHR, SHL, // ROL, ROR, RCL, RCR, SAR, SAL,
    END
};