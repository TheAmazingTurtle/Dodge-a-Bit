#pragma once
#include <raylib.h>
#include "../Utils/Config.h"

class Player {
public:
    Player();
    ~Player();

    // Methods
    void Update(float deltaTime);
    void Draw() const;
    void Move(float dx, float dy);
    void TakeHit();
    void ResetValues();
    void ResetHitFlags();

    // Getters
    Rectangle GetHitbox() const;
    Vector2 GetPosition() const;
    int GetLivesLeft() const;
    bool IsHit() const;
    bool isDead() const;

private:
    enum class Direction {
        Left, Right
    };

    enum class PlayerState {
        IDLE, WALKING, DASHING, DYING
    };

    static constexpr int IDLE_FRAME_COUNT = 1;
    static constexpr int WALKING_FRAME_COUNT = 8;
    static constexpr int DASHING_FRAME_COUNT = 7;
    static constexpr int DYING_FRAME_COUNT = 5;
    static constexpr int SHEET_UNIT_WIDTH = 8;
    static constexpr int SHEET_UNIT_HEIGHT = 4;
    static constexpr int FRAME_SPEED = 12;

    static constexpr float DASH_DURATION = 1.0f / FRAME_SPEED * DASHING_FRAME_COUNT;
    static constexpr float DYING_DURATION = 1.0f / FRAME_SPEED * DYING_FRAME_COUNT;
    static constexpr float DASH_SPEED = 400.0f;
    static constexpr float WALK_SPEED = 200.0f;
    static constexpr int WIDTH = 48;
    static constexpr int HEIGHT = 64;

    // static constexpr int FRAME_WIDTH = m_spriteFrame.width;
    // static constexpr int FRAME_HEIGHT = m_spriteFrame.height;
    
    Texture2D m_spriteSheet;
    Rectangle m_spriteFrame;
    int m_frameWidth;
    int m_frameHeight;

    Vector2 m_position;
    
    int m_life;
    bool m_hit;
    bool m_isLifeDeducted;

    PlayerState m_oldState;
    Direction m_direction;
    float m_frameCounter;
    float m_dashTimer;
    bool m_dashing;
    bool m_dying;
    bool m_dead;

    void clampToScreen();
};