#pragma once
#include <raylib.h>
// #include <string>

class Turret {
public:
    // Constructor / Destructor
    Turret(const Vector2& basePos, int index);
    ~Turret();

    // Methods
    void Update(float deltaTime);
    void Draw() const;
    void FireTurret();

    // Getter
    Rectangle GetLaserHitbox() const;
    Vector2 GetPosition() const;
    bool GetIsActive() const;

private:
    const float activeDuration;
    float fireTimer;
    float fireInterval;
    
    // Texture2D texture;
    int index;
    Vector2 position;
    bool isActive;
    float activeTimer;
};