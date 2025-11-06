#pragma once
#include <raylib.h>
#include "config.hpp"

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
    const float m_invincibilityDuration;
    float m_invincibilityTimer;

    // for dash
    Direction m_direction;
    bool m_isDashing;
    float m_dashTimer;
    const float m_dashDuration;
    const float m_dashSpeed;

    Texture2D m_texture;
    Vector2 m_position;
    int m_life;
    const float m_speed;
    bool m_isHit;
    bool m_isLifeDeducted;

    // Internal helpers
    void clampToScreen();
};
