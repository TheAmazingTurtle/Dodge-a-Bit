#include <raylib.h>
#include "StartScreen.h"
#include "HUD.h"
#include "Player.h"
#include "Turret.h"
#include <vector>


#define UNIT_SIZE 64
#define NUM_TURRETS 8
unsigned char testByte = 0b10101010;


enum class GameState {
    StartScreen, 
    GameOngoing,
    GameOver,
    GameWin
};

int main() {
    const int screenWidth = UNIT_SIZE * 10;
    const int screenHeight = UNIT_SIZE * 15;
    // Color green = {20, 160, 133, 255};
    InitWindow(screenWidth, screenHeight, "Dodge-a-Bit");

    SetTargetFPS(60);

    // GAME STATE
    GameState gameState = GameState :: GameOngoing;

    // START SCREEN
    StartScreen startScreen({});

    // WAVE TRACKING
    int currentWave = 1;
    int recordedHighestWave = 1;


    // CREATING 8 TURRETS
    std::vector<Turret> turrets;
    turrets.reserve(NUM_TURRETS);

    float yTurret = UNIT_SIZE * 2.0f;
    float xTurOffset = (screenWidth - (NUM_TURRETS * UNIT_SIZE)) / 2.0f;
    for (int i = 0; i < NUM_TURRETS; i++){
        Vector2 position = {xTurOffset + (i* UNIT_SIZE), yTurret};
        turrets.emplace_back(position, i);

    }

    // PLAYING
    Player player({screenWidth/2, screenHeight - UNIT_SIZE*2});
    HUD hud({});

    
    

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);

        switch (gameState) {
            case GameState::StartScreen:
                startScreen.Draw();
                break;
            case GameState::GameOngoing:
                player.Update(deltaTime);
                
                // Event Handling
                for (auto &t : turrets) t.Update(deltaTime);
                
                for (auto &t : turrets) {
                    if (!player.GetIsHit() && t.GetIsActive() && CheckCollisionRecs(player.GetHitbox(), t.GetLaserHitbox())){
                        player.TakeHit();
                        break;
                    }
                }
                
                if (player.GetLife() <= 0) gameState = GameState::GameOver;
                if (currentWave > 10) gameState = GameState::GameWin;
                
                for (const auto &t : turrets) t.Draw();
                player.Draw();
                hud.Draw(player, currentWave, recordedHighestWave);
                
                break;

            case GameState::GameOver:
                break;
            case GameState::GameWin:
                break;
        }


        

        // Drawing

        EndDrawing();
    }
    return 0;
}