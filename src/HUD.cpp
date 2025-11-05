#include "HUD.h"
#include <string>


HUD::HUD() {}

HUD::~HUD() {}

void HUD::Draw(const Player &player, int currentWave, int recordedHighestWave) const{
    // Draw texts
    DrawCurrentWave(currentWave);
    DrawHighestWaveReached(recordedHighestWave);

    // Draw lives
    for (int i = 0; i < player.GetLife(); i++){
        DrawLifeIcon(i);
    }
}

void HUD::DrawCurrentWave(int currentWave) const {
    DrawText(TextFormat("WAVE: %d/10", currentWave), baseX * 4.5, baseY + 8, 20, WHITE);
}

void HUD::DrawHighestWaveReached(int recordedHighestWave) const {
    DrawText(TextFormat("HIGHEST WAVE: %d", recordedHighestWave), baseX * 8.5, baseY + 8, 20, WHITE);
}

void HUD::DrawLifeIcon(int index) const {
    float x = baseX + index * (iconSize + iconPadding);
    float y = baseY;
    
    Vector2 v1 = { x , y };
    Vector2 v2 = { x - iconSize / 2.0f, y + iconSize };
    Vector2 v3 = { x + iconSize / 2.0f, y + iconSize };

    DrawTriangle(v1, v2, v3, PINK); 
}

