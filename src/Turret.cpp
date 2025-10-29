#include "Turret.h"

Turret::Turret(const Vector2& basePos) : activeDuration(1.0f), position(basePos), isActive(false), activeTimer(0.0f) {}
Turret::~Turret() {}

void Turret::Update(float deltaTime) {
    if (IsKeyDown(KEY_ENTER)){
        isActive = true;
    }


    if (isActive) {
        activeTimer += deltaTime;
        if (activeTimer >= activeDuration) {
            isActive = false;
            activeTimer = 0.0f;
        }
    }
}

void Turret::Draw() const {
    DrawCircle(position.x + 32, position.y + 32, 32, WHITE);

    if (isActive) DrawRectangle(position.x, position.y + 64, 64, 64*11, WHITE);
}

void Turret::FireTurret() {
    isActive = true;
}

Rectangle Turret::GetLaserHitbox() const {
    return {position.x, position.y + 64, 64, 64*11};
}

Vector2 Turret::GetPosition() const {
    return position;
}

bool Turret::GetIsActive() const {
    return isActive;
}