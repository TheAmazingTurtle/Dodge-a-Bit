#include "Turret.h"

Turret::Turret(const Vector2& basePos) : 
    m_position(basePos), 
    m_isShooting(false),
    m_isActive(false), 
    m_activeTimer(0.0f) {

        m_spriteSheet = LoadTexture("../../graphics/turret-spritesheet.png");
        m_laserSpriteSheet = LoadTexture("../../graphics/laser-spritesheet.png");
}

Turret::~Turret() {
    UnloadTexture(m_spriteSheet);
    UnloadTexture(m_laserSpriteSheet);
}

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
    Rectangle spriteFrame = {0.0f, 0.0f, Config::UNIT_SIZE, Config::UNIT_SIZE};

    if (m_isActive) {
        spriteFrame.x = Config::UNIT_SIZE;
    }
    DrawTextureRec(m_spriteSheet, spriteFrame, {m_position.x, m_position.y}, WHITE);

    if (m_isShooting) {
        spriteFrame.x = 0.0f + (int)(m_activeTimer / (1.0f / LASER_FRAME_COUNT)) * Config::UNIT_SIZE;
        spriteFrame.y = 0.0f;
        for (int i = 0; i < 12; i++) {
            DrawTextureRec(m_laserSpriteSheet, spriteFrame, {m_position.x, m_position.y + Config::UNIT_SIZE*(i+1)}, WHITE);
        }
    }

    

    // if (m_isActive && m_isShooting) {}
    // DrawTextureRec(m_spriteSheet, m_spriteFrame, {m_position.x - Config::UNIT_SIZE/2, m_position.y - Config::UNIT_SIZE}, WHITE);
    
    // DrawCircle(m_position.x + 32, m_position.y + 32, 32, WHITE);

    // if (m_isShooting) DrawRectangle(m_position.x + 16, m_position.y + 64, 32, 64*12, WHITE);

    // const char* activeStatus = TextFormat(m_isActive ? "1" : "0");
    // DrawText(activeStatus, m_position.x + (64 - MeasureText(activeStatus, 30))/2, m_position.y + (64 - 30)/2, 30, BLACK);
}

void Turret::shootLaser() {
    if (!m_isActive) return;
    m_isShooting = true;
}

void Turret::setIsActive(bool isActive) {
    m_isActive = isActive;
}

Rectangle Turret::getLaserHitbox() const {
    return {m_position.x + 14, m_position.y + 64, 36, 64*12};
}

Vector2 Turret::getPosition() const {
    return m_position;
}

bool Turret::getIsShooting() const {
    return m_isShooting;
}