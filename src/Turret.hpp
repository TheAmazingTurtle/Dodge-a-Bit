#pragma once
#include <raylib.h>

class Turret {
public:
    Turret(const Vector2& basePos);
    ~Turret();

    void update(float deltaTime);
    void draw() const;
    void shootLaser();

    Rectangle getLaserHitbox() const;
    Vector2 getPosition() const;
    bool getIsShooting() const;

private:
    const float m_activeDuration;
    float m_fireTimer;
    float m_fireInterval;
    
    // Texture2D texture;
    int m_index;
    Vector2 m_position;
    bool m_isShooting;
    float m_activeTimer;
};