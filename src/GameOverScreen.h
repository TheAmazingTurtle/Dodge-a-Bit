#pragma once
#include <raylib.h>
#include "Utils/Button.h"

enum class GameOverScreenAction {
    None,
    TryAgain,
    Exit,
};

class GameOverScreen {
public:
    GameOverScreen() ;
    ~GameOverScreen();

    // Methods
    // void LoadResources();
    // void UnloadResources();

    void Draw() const;
    void Update();

    bool IsTryAgainPressed() const;
    bool IsExitPressed() const;

    void SetWaveReached(int waveNumber);
    // void SetIconSize();
    // void SetIconPadding();
    // void SetBasePosition();

private:
   GameOverScreenAction gameOverAction;
    
    Button tryAgainButton;
    Button exitButton;

    // Data members
    // int iconSize = 30; 
    // int iconPadding = 8;
    // int baseX = 50;
    // int baseY = 30;
    int waveReached; 

    // Texture2D texture;
    // Vector2 position;

    //helper
    void DrawGameOverText() const;
    void DrawButtons() const;

};
