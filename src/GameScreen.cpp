#include "GameScreen.hpp"

GameScreen::GameScreen() {
    // turret
    int numTurrets = 8;
    turrets.reserve(numTurrets);

    float yTurretOffset = UNIT_SIZE;
    float xTurretOffset = (SCREEN_WIDTH - UNIT_SIZE * numTurrets) / 2;
    for (int i = 0; i < numTurrets; i++){
        Vector2 position = {xTurretOffset + (i* UNIT_SIZE), yTurretOffset};
        turrets.emplace_back(position);
    }
};

void GameScreen::draw() const {
    ClearBackground(BLACK);

    drawHighscore();
    for (int i = 0; i < player.getLivesLeft(); i++) drawLifeIcon(i);

    for (const Turret &turret : turrets) turret.draw();
    player.draw();
}

void GameScreen::update(float deltaTime) {
    player.update(deltaTime);
    for (Turret &turret : turrets) turret.update(deltaTime);
                
    if (!player.getIsHit()) {
        for (Turret &turret : turrets) {
            if (turret.getIsShooting() && CheckCollisionRecs(player.getHitbox(), turret.getLaserHitbox())){
                player.takeHit();
                break;
            }
        }
    }
    
    
    // if (player.getLivesLeft() <= 0)
}

void GameScreen::drawLifeIcon(int index) const {
    int iconSize = 30; 
    int iconPadding = 8;
    int baseX = 50;
    int baseY = 30;

    float x = baseX + index * (iconSize + iconPadding);
    float y = baseY;
    
    Vector2 v1 = { x , y };
    Vector2 v2 = { x - iconSize / 2.0f, y + iconSize };
    Vector2 v3 = { x + iconSize / 2.0f, y + iconSize };

    DrawTriangle(v1, v2, v3, PINK); 
}

void GameScreen::drawHighscore() const {
    int baseX = 50;
    int baseY = 30;

    int highscore = 10;
    DrawText(TextFormat("HIGHEST WAVE: %d", highscore), baseX * 8.5, baseY + 8, 20, WHITE);
}