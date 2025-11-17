#include <raylib.h>

#include "Game.h"
#include "GameStates/StartState.h"

int main() {
    Game game;
    game.ChangeState(std::make_unique<StartState>());
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