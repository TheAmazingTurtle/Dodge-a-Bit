#include "Turret.h"
extern unsigned char testByte;

Turret::Turret(const Vector2& basePos, int i) : activeDuration(1.0f), fireTimer(0.0f), fireInterval(2.0f), index(i), position(basePos), isActive(false), activeTimer(0.0f){}
Turret::~Turret() {}

void Turret::Update(float deltaTime) { 
    if (!isActive) {
        fireTimer += deltaTime;
        if (fireTimer >= fireInterval){
            fireTimer = 0.0f;
            if ((testByte >> (7 - index)) & 1){
                FireTurret();
            }
            
        }
    } else {
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