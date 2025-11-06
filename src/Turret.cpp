#include "Turret.hpp"
extern unsigned char testByte;

Turret::Turret(const Vector2& basePos) : 
    m_activeDuration(1.0f), 
    m_fireTimer(0.0f), 
    m_fireInterval(2.0f), 
    m_position(basePos), 
    m_isShooting(false), 
    m_activeTimer(0.0f) {}
Turret::~Turret() {}

void Turret::update(float deltaTime) { 
    if (!m_isShooting) {
        m_fireTimer += deltaTime;
        if (m_fireTimer >= m_fireInterval){
            m_fireTimer = 0.0f;
            m_isShooting = true;
        }
    } else {
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
}

void Turret::shootLaser() {
    m_isShooting = true;
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