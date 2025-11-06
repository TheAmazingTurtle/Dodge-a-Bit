#pragma once

enum class Direction:char {
    Left, Right
};

constexpr char *GAME_TITLE = "Dodge-a-Bit";
constexpr int UNIT_SIZE = 64;
constexpr int SCREEN_WIDTH = UNIT_SIZE * 10;
constexpr int SCREEN_HEIGHT = UNIT_SIZE * 15;