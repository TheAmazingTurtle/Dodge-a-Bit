#pragma once 
#include <raylib.h>

class Button {
public:
    Button(const char *buttonLabel, Vector2 buttonPosition, Vector2 scale);
    ~Button() = default;

    void Draw() const;
    bool IsPressed(Vector2 mousePos, bool isMousePressed) const;

    void SetPosition(Vector2 newPos);
    void SetLabel(const char *newLabel);
    
    Vector2 GetPosition() const;

private: 
    // Texture2D texture;
    // Vector2 position;

    const char *label;
    Vector2 position;
    Vector2 scale;
    Color normalColor;
    Color hoverColor;
    Color textColor;

    // Texture2D texture;
    
};