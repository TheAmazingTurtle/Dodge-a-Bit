#include "Player.h"

Player::Player() : 
    m_position({Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT - Config::UNIT_SIZE*2}),
    m_life(3),
    m_gotHit(false), 
    m_isLifeDeducted(false) ,
    m_direction(Direction::Right), 
    m_isDashing(false), 
    m_dashTimer(0.0f)
 {}

Player::~Player() {}

void Player::Update(float deltaTime) {
    if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !m_isDashing){
        m_isDashing = true;
        m_dashTimer = 0.0f;
    }
    
    // dashing
    if (m_isDashing){
        switch (m_direction)
        {
        case Direction::Right:
            m_position.x += Config::PLAYER_DASH_SPEED * deltaTime;
            break;
        case Direction::Left:
            m_position.x -= Config::PLAYER_DASH_SPEED * deltaTime;
            break;
        }
        
        m_dashTimer += deltaTime;
        if (m_dashTimer >= Config::PLAYER_DASH_DURATION) m_isDashing = false;

    } else {
        if (IsKeyDown(KEY_LEFT)) {
            m_direction = Direction::Left;
            m_position.x -= Config::PLAYER_SPEED * deltaTime;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            m_direction = Direction::Right;
            m_position.x += Config::PLAYER_SPEED * deltaTime;
        }

    }
 
    // laser collision
    if (m_gotHit && !m_isLifeDeducted){
        m_life--;
        m_isLifeDeducted = true;
    }

    clampToScreen();
}

void Player::Draw() const {
    DrawRectangle(m_position.x, m_position.y, 48, 64, m_gotHit ? RED : WHITE);
}

void Player::Move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
}

void Player::ResetHitFlags() {
    m_gotHit = false;
    m_isLifeDeducted = false;
}

void Player::TakeHit() {
    m_gotHit = true;
}

Rectangle Player::GetHitbox() const {
    return {m_position.x, m_position.y, 48, 64};
}

Vector2 Player::GetPosition() const {
    return m_position;
}

int Player::GetLivesLeft() const {
    return m_life;
}

bool Player::IsHit() const {
    return m_gotHit;
}

void Player::clampToScreen() {
    if (m_position.x <= 64) m_position.x = 64;
    if (m_position.y < 0) m_position.y = 0;
    if (m_position.x >= Config::SCREEN_WIDTH - 110) m_position.x = Config::SCREEN_WIDTH - 110;
    if (m_position.y > Config::SCREEN_HEIGHT - 64) m_position.y = Config::SCREEN_HEIGHT - 64;
}