#include "Button.h"
// #include <iostream>

Button::Button(const char *buttonLabel, Vector2 buttonPosition, Vector2 buttonScale): label(buttonLabel), position(buttonPosition), scale(buttonScale), normalColor(DARKGRAY), hoverColor(GRAY), textColor(WHITE){}

void Button::Draw() const {
    Rectangle rect = {position.x,position.y,scale.x,scale.y};
    Vector2 mousePos = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mousePos, rect);

    Color drawColor = isHovered ? hoverColor : normalColor;


    DrawRectangleRounded(rect, 0.3f, 8, drawColor);
    DrawRectangleRoundedLines(rect, 0.3f, 8, normalColor);
    int fontSize = 20;
    int textWidth = MeasureText(label,fontSize);
    float textY = position.y + (scale.y - fontSize) / 2;
    DrawText(label, position.x + (scale.x - textWidth) / 2, textY, fontSize, textColor);
}

bool Button::IsPressed(Vector2 mousePos, bool isMousePressed) const {
    return isMousePressed && CheckCollisionPointRec(mousePos, {position.x,position.y,scale.x,scale.y});
}

void Button::SetLabel(const char *newLabel){
    label = newLabel;
}

void Button::SetPosition(Vector2 newPos){
    position = newPos;
}

Vector2 Button::GetPosition() const{
    return position;
}
