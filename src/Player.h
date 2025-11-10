#pragma once
#include <raylib.h>
#include "config.h"

class Player {
public:
    // Constructor / Destructor
    // Player(const Vector2& startPos, const std::string& texturePath);
    Player();
    Player(const Vector2& startPos);
    ~Player();

    // Methods
    void update(float deltaTime);
    void draw() const;
    void move(float dx, float dy);
    void takeHit();
    void resetValues();

    // Getters
    Rectangle getHitbox() const;
    Vector2 getPosition() const;
    int getLivesLeft() const;
    bool getIsHit() const;

private:
    static const float m_invincibilityDuration;
    static const float m_dashDuration;
    static const float m_dashSpeed;
    static const float m_speed;
    static const int m_width;
    static const int m_height;
    
    Texture2D m_texture;
    Vector2 m_position;
    
    float m_invincibilityTimer;
    int m_life;
    bool m_isHit;
    bool m_isLifeDeducted;

    Direction m_direction;
    bool m_isDashing;
    float m_dashTimer;

    void clampToScreen();
};