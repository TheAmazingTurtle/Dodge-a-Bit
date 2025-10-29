#pragma once
#include <raylib.h>
// #include <string>

class Turret {
public:
    // Constructor / Destructor
    Turret(const Vector2& basePos);
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
    // Texture2D texture;
    Vector2 position;
    bool isActive;
    float activeTimer;
};