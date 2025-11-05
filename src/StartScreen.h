#pragma once
#include <raylib.h>
// #include <string>

class StartScreen {
public:
    StartScreen() ;
    ~StartScreen();

    // Methods
    // void LoadResources();
    // void UnloadResources();

    void Draw() const;
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

    void DrawGameTitle() const;
    void DrawPlayText() const;
    void DrawMusicOnText() const;
    void DrawSoundOnText() const;
    void DrawInstructionsText() const;
    void DrawExitText() const;
};
