#include <raylib.h>

int main() {
    int playerX = 400;
    int playerY = 400;
    Color green = {20, 160, 133, 255};


    InitWindow(800, 800, "Dodge-a-Bit");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        // Event Handling


        // Update Position
        if (IsKeyDown(KEY_RIGHT)){
            playerX += 3;
        }

        


        // Drawing
        BeginDrawing();
        ClearBackground(green);

        DrawRectangle(playerX, playerY, 20, 20, BLUE);

        EndDrawing();
    }
    

    return 0;
}