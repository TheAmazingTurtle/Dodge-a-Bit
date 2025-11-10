#include "Player.h"

const float Player::m_invincibilityDuration = 1.0f;
const float Player::m_dashDuration = 0.13f;
const float Player::m_dashSpeed = 700.0f;
const float Player::m_speed = 200.0f;
const int Player::m_width = 48;
const int Player::m_height = 64;

Player::Player() : 
    m_position({SCREEN_WIDTH/2, SCREEN_HEIGHT - UNIT_SIZE*2}), 
    m_invincibilityTimer(0.0f),
    m_life(3),
    m_isHit(false), 
    m_isLifeDeducted(false) ,
    m_direction(Direction::Right), 
    m_isDashing(false), 
    m_dashTimer(0.0f)
 {}

Player::~Player() {}

void Player::update(float deltaTime) {
    if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !m_isDashing){
        m_isDashing = true;
        m_dashTimer = 0.0f;
    }
    
    // dashing
    if (m_isDashing){
        switch (m_direction)
        {
        case Direction::Right:
            m_position.x += m_dashSpeed * deltaTime;
            break;
        case Direction::Left:
            m_position.x -= m_dashSpeed * deltaTime;
            break;
        }
        
        m_dashTimer += deltaTime;
        if (m_dashTimer >= m_dashDuration) m_isDashing = false;

    } else {
        if (IsKeyDown(KEY_LEFT)) {
            m_direction = Direction::Left;
            m_position.x -= m_speed * deltaTime;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            m_direction = Direction::Right;
            m_position.x += m_speed * deltaTime;
        }

    }
 
    // laser collision
    if (m_isHit){
        if (!m_isLifeDeducted) {
            m_life--;
            m_isLifeDeducted = true;
        }

        m_invincibilityTimer += deltaTime;
        if (m_invincibilityTimer >= m_invincibilityDuration){
            m_isHit = false;
            m_isLifeDeducted = false;
            m_invincibilityTimer = 0.0f;
        }
    }

    clampToScreen();
}

void Player::draw() const {
    DrawRectangle(m_position.x, m_position.y, 48, 64, m_isHit ? RED : WHITE);
}

void Player::move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
}

void Player::takeHit() {
    m_isHit = true;
}

Rectangle Player::getHitbox() const {
    return {m_position.x, m_position.y, 48, 64};
}

Vector2 Player::getPosition() const {
    return m_position;
}

int Player::getLivesLeft() const {
    return m_life;
}

bool Player::getIsHit() const {
    return m_isHit;
}

void Player::clampToScreen() {
    if (m_position.x <= 64) m_position.x = 64;
    if (m_position.y < 0) m_position.y = 0;
    if (m_position.x >= SCREEN_WIDTH - 110) m_position.x = SCREEN_WIDTH - 110;
    if (m_position.y > SCREEN_HEIGHT - 64) m_position.y = SCREEN_HEIGHT - 64;
}

// Player::Player(const Vector2& startPos, const std::string& texturePath)
//     : position(startPos), health(100), speed(200.0f) // pixels per second
// {
//     texture = LoadTexture(texturePath.c_str());
// }

// Player::~Player() {
//     UnloadTexture(texture);
// }

// void Player::Update(float deltaTime) {
//     // Example movement with WASD
//     if (IsKeyDown(KEY_W)) position.y -= speed * deltaTime;
//     if (IsKeyDown(KEY_S)) position.y += speed * deltaTime;
//     if (IsKeyDown(KEY_A)) position.x -= speed * deltaTime;
//     if (IsKeyDown(KEY_D)) position.x += speed * deltaTime;

//     ClampToScreen();
// }

// void Player::Draw() const {
//     DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
// }

// void Player::Move(float dx, float dy) {
//     position.x += dx;
//     position.y += dy;
// }

// Vector2 Player::GetPosition() const {
//     return position;
// }

// int Player::GetHealth() const {
//     return health;
// }

// void Player::ClampToScreen() {
//     // Prevent player from leaving window boundaries
//     int screenWidth = GetScreenWidth();
//     int screenHeight = GetScreenHeight();

//     if (position.x < 0) position.x = 0;
//     if (position.y < 0) position.y = 0;
//     if (position.x > screenWidth - texture.width) position.x = screenWidth - texture.width;
//     if (position.y > screenHeight - texture.height) position.y = screenHeight - texture.height;
// }