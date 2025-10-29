#include <raylib.h>
#include "Player.h"
#include "Turret.h"

#define UNIT_SIZE 64

int main() {
    const int screenWidth = UNIT_SIZE * 10;
    const int screenHeight = UNIT_SIZE * 15;
    // Color green = {20, 160, 133, 255};
    InitWindow(screenWidth, screenHeight, "Dodge-a-Bit");

    SetTargetFPS(60);

    Player player({screenWidth/2, screenHeight - UNIT_SIZE*2});
    Turret turret({UNIT_SIZE, UNIT_SIZE*2});

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Event Handling
        if (!player.GetIsHit() && turret.GetIsActive() && CheckCollisionRecs(player.GetHitbox(), turret.GetLaserHitbox())){
            player.TakeHit();
        }

        player.Update(deltaTime);
        turret.Update(deltaTime);

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        turret.Draw();
        player.Draw();

        EndDrawing();
    }
    

    return 0;
}