#pragma once
#include <raylib.h>
// #include <string>

class Player {
public:
    // Constructor / Destructor
    // Player(const Vector2& startPos, const std::string& texturePath);
    Player(const Vector2& startPos);
    ~Player();

    // Methods
    void Update(float deltaTime);
    void Draw() const;
    void Move(float dx, float dy);
    void TakeHit();

    // Getters
    Rectangle GetHitbox() const;
    Vector2 GetPosition() const;
    int GetLife() const;
    bool GetIsHit() const;

private:
    // Data members
    const float invincibilityDuration;
    float invincibilityTimer;

    Texture2D texture;
    Vector2 position;
    int life;
    float speed;
    bool isHit;
    bool isLifeDeducted;

    // Internal helpers
    void ClampToScreen();
};
