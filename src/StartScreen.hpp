#pragma once
#include "Screen.hpp"
#include <raylib.h>

class StartScreen : public Screen {
public:
    StartScreen() ;
    ~StartScreen();

    void draw() const override;
    void update(float deltaTime) override;

    // Methods
    // void LoadResources();
    // void UnloadResources();
    // void SetIconSize();
    // void SetIconPadding();
    // void SetBasePosition();

private:
    // Data members
    // int iconSize = 30; 
    // int iconPadding = 8;
    // int baseX = 50;
    // int baseY = 30;

    // Texture2D texture;
    // Vector2 position;
};
