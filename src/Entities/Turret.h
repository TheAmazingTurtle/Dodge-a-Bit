#pragma once
#include <raylib.h>

class Turret {
public:
    Turret(const Vector2& basePos);
    ~Turret();

    void update(float deltaTime);
    void draw() const;
    void shootLaser();

    void setIsActive(bool isActive);
    Rectangle getLaserHitbox() const;
    Vector2 getPosition() const;
    bool getIsShooting() const;

private:
    static const float m_activeDuration;

    Vector2 m_position;

    float m_fireTimer;
    bool m_isShooting;
    bool m_isActive;
    float m_activeTimer;
};