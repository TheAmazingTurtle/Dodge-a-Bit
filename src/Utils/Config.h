#pragma once

namespace Config {
    constexpr int TURRET_NUM = 8;

    constexpr int UNIT_SIZE = 64;
    constexpr int SCREEN_WIDTH  = 576;
    constexpr int SCREEN_HEIGHT = 1024;
    constexpr int SIDE_PADDING = (SCREEN_WIDTH - UNIT_SIZE*TURRET_NUM) / 2;
}



