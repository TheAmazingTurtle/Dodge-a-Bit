#pragma once
#include <raylib.h>
#include "../Utils/Config.h"

class Player {
public:
    Player();
    Player(const Vector2& startPos);
    ~Player();

    // Methods
    void Update(float deltaTime);
    void Draw() const;
    void Move(float dx, float dy);
    void TakeHit();
    void ResetValues();
    void ResetHitFlags();

    // Getters
    Rectangle GetHitbox() const;
    Vector2 GetPosition() const;
    int GetLivesLeft() const;
    bool IsHit() const;

private:
    enum class Direction {
        Left, Right
    };
    
    Texture2D m_texture;
    Vector2 m_position;
    
    int m_life;
    bool m_gotHit;
    bool m_isLifeDeducted;

    Direction m_direction;
    bool m_isDashing;
    float m_dashTimer;

    void clampToScreen();
};