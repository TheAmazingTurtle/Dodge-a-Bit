#pragma once 
#include <raylib.h>

class Button {
public:
    Button(const char *buttonLabel, Vector2 buttonPosition);
    ~Button();

    void Draw(const char *buttonLabel) const;

private: 
    // Texture2D texture;
    char *label;
    Vector2 position;

};