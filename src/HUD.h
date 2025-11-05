#pragma once
#include <raylib.h>
#include "Player.h"
// #include <string>

class HUD {
public:
    // Constructor / Destructor
    // Player(const Vector2& startPos, const std::string& texturePath);
    HUD() ;
    ~HUD();

    // Methods
    // void LoadResources();
    // void UnloadResources();

    void Draw(const Player &player, int currentWave, int recordedHighestWave) const;
    // void SetIconSize();
    // void SetIconPadding();
    // void SetBasePosition();

private:
    // Data members
    int iconSize = 30; 
    int iconPadding = 8;
    int baseX = 50;
    int baseY = 30;

    Texture2D texture;
    // Vector2 position;

    void DrawLifeIcon(int index) const; // triangle for now
    void DrawCurrentWave(int currentWave) const;
    void DrawHighestWaveReached(int recordedHighestWave) const;
};
