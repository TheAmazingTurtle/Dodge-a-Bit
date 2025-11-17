#include "Turret.h"

const float Turret::m_activeDuration = 1.0f;

Turret::Turret(const Vector2& basePos) : 
    m_position(basePos), 
    m_fireTimer(0.0f),
    m_isShooting(false),
    m_isActive(false), 
    m_activeTimer(0.0f) {}
Turret::~Turret() {}

void Turret::update(float deltaTime) { 
    if (m_isShooting) {
        m_activeTimer += deltaTime;
        if (m_activeTimer >= m_activeDuration) {
            m_isShooting = false;
            m_activeTimer = 0.0f;
        }  
    }
}

void Turret::draw() const {
    DrawCircle(m_position.x + 32, m_position.y + 32, 32, WHITE);

    if (m_isShooting) DrawRectangle(m_position.x + 16, m_position.y + 64, 32, 64*12, WHITE);

    const char* activeStatus = TextFormat(m_isActive ? "1" : "0");
    DrawText(activeStatus, m_position.x + (64 - MeasureText(activeStatus, 30))/2, m_position.y + (64 - 30)/2, 30, BLACK);
}

void Turret::shootLaser() {
    if (!m_isActive) return;
    m_isShooting = true;
}

void Turret::setIsActive(bool isActive) {
    m_isActive = isActive;
}

Rectangle Turret::getLaserHitbox() const {
    return {m_position.x + 16, m_position.y + 64, 32, 64*12};
}

Vector2 Turret::getPosition() const {
    return m_position;
}

bool Turret::getIsShooting() const {
    return m_isShooting;
}