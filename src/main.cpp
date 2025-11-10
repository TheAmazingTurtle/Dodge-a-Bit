#include <raylib.h>

#include "config.h"

#include "Player.h"
#include "Screen.h"
#include "Guardian.h"

#include <vector>


Screen screen;
Player player;
Guardian guardian;

GameState g_gameState;
int g_currentScore;

void initGame(){
    g_gameState = GameState::GameOngoing;
    g_currentScore = 0;
}

// void processStartScreen() {
    
//     startScreen.Update();
//     if (startScreen.IsPlayPressed()) gameState = GameState::GameOngoing;
//     if (startScreen.IsExitPressed()) {
//         CloseWindow();
//         return 0;
//     }

//     BeginDrawing();
    
//     ClearBackground(BLACK);
//     startScreen.Draw();

//     EndDrawing();
// }

void processGameScreen() {
    float deltaTime = GetFrameTime();

    // Event Management
    player.update(deltaTime);
    guardian.update(deltaTime);
    
    if (!player.getIsHit() && guardian.doTurretsHit(player.getHitbox())) player.takeHit();
    if (player.getLivesLeft() <= 0) g_gameState = GameState::GameOver;
    
    // Drawing
    BeginDrawing();

    ClearBackground(BLACK);
    screen.drawHeadupDisplay(player.getLivesLeft(), g_currentScore, 100);
    guardian.draw();
    player.draw();

    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dodge-a-Bit");
    SetTargetFPS(60);

    initGame();

    while (!WindowShouldClose()) {
        switch (g_gameState) {
            case GameState::StartScreen:
                break;
            case GameState::GameOngoing: processGameScreen(); break;
            case GameState::GameOver: 
                // gameOverScreen.Draw();
                // gameOverScreen.SetWaveReached(currentWave);
                // gameOverScreen.Update();
                // if (gameOverScreen.IsTryAgainPressed()) gameState = GameState::GameOngoing;
                // if (gameOverScreen.IsExitPressed()) {
                //     CloseWindow();
                //     return 0;
                // }
                break;
            case GameState::GameWin: 
                break;
            
        }
    }
    return 0;
}