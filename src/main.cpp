#include <raylib.h>

#include "Game.h"
#include "GameStates/GameplayState.h"

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

int main() {
    Game game;
    game.ChangeState(std::make_unique<GameplayState>());
    game.Run();
}

// case GameState::GameOver: 
    //             // gameOverScreen.Draw();
    //             // gameOverScreen.SetWaveReached(currentWave);
    //             // gameOverScreen.Update();
    //             // if (gameOverScreen.IsTryAgainPressed()) gameState = GameState::GameOngoing;
    //             // if (gameOverScreen.IsExitPressed()) {
    //             //     CloseWindow();
    //             //     return 0;
    //             // }
    //             break;