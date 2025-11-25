#pragma once

#include "../Utils/Config.h"

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
    static constexpr float m_activeDuration = 1.0f;
    static constexpr int LASER_FRAME_COUNT = 14;
    static constexpr int SHEET_UNIT_WIDTH = 2;
    static constexpr int SHEET_UNIT_HEIGHT = 3;

    Texture2D m_spriteSheet;
    Texture2D m_laserSpriteSheet;

    Vector2 m_position;
    bool m_isShooting;
    bool m_isActive;
    float m_activeTimer;
};