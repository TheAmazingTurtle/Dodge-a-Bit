#pragma once

class Screen
{
public:
    ~Screen() = default;

    virtual void draw() const = 0;
    virtual void update(float deltaTime) = 0;
};