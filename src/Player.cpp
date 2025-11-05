#include "Player.h"
#include <iostream>

Player::Player(const Vector2& startPos) : invincibilityDuration(1.0f), invincibilityTimer(0.0f), isFacingRight(false), isDashing(false), dashTimer(0.0f), dashDuration(0.13f), dashSpeed(700.0f), position(startPos), life(3), speed(200.0f), isHit(false), isLifeDeducted(false) {}
Player::~Player() {}

void Player::Update(float deltaTime) {
    if (IsKeyPressed(KEY_RIGHT)) {
        std::cout << "player facing RIGHT\n";
        isFacingRight = true;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        std::cout << "player facing LEFT\n";
        isFacingRight = false;
    }
    if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !isDashing){
        isDashing = true;
        dashTimer = 0.0f;
    }
    
    if (isDashing){
        // DASH MOVEMENT
        if (isFacingRight) position.x += dashSpeed * deltaTime;
        else position.x -= dashSpeed * deltaTime;
        
        dashTimer += deltaTime;
        if (dashTimer >= dashDuration) isDashing = false;

    } else {
        // LEFT & RIGHT Movement
        if (IsKeyDown(KEY_LEFT)) position.x -= speed * deltaTime;
        if (IsKeyDown(KEY_RIGHT)) position.x += speed * deltaTime;
    }
 
    // Laser Collision
    if (isHit){
        if (!isLifeDeducted) {
            life--;
            isLifeDeducted = true;
        }

        invincibilityTimer += deltaTime;
        if (invincibilityTimer >= invincibilityDuration){
            isHit = false;
            isLifeDeducted = false;
            invincibilityTimer = 0.0f;
        }
    }

    ClampToScreen();
}

void Player::Draw() const {
    DrawRectangle(position.x, position.y, 48, 64, isHit ? RED : WHITE);
}

void Player::Move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void Player::TakeHit() {
    isHit = true;
}

Rectangle Player::GetHitbox() const {
    return {position.x, position.y, 48, 64};
}

Vector2 Player::GetPosition() const {
    return position;
}

int Player::GetLife() const {
    return life;
}

bool Player::GetIsHit() const {
    return isHit;
}

void Player::ClampToScreen() {
    // Prevent player from leaving window boundaries
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    if (position.x <= 64) position.x = 64;
    if (position.y < 0) position.y = 0;
    if (position.x >= screenWidth - 110) position.x = screenWidth - 110;
    if (position.y > screenHeight - 64) position.y = screenHeight - 64;
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
