#include "Player.h"
#include <iostream>

Player::Player() : 
    m_position({Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT - Config::UNIT_SIZE}),
    m_life(3),
    m_hit(false), 
    m_isLifeDeducted(false),
    m_oldState(PlayerState::IDLE),
    m_direction(Direction::Right),
    m_frameCounter(0),
    m_dashTimer(0.0f),
    m_tapTimer(0.0f),
    m_dashing(false),
    m_dying(false),
    m_dead(false) {

    m_spriteSheet = LoadTexture("../../graphics/player-spritesheet.png");

    m_frameWidth  = m_spriteSheet.width / SHEET_UNIT_WIDTH;
    m_frameHeight = m_spriteSheet.height / SHEET_UNIT_HEIGHT;

    m_spriteFrame = { 0.0f, 0.0f, (float)m_frameWidth, (float)m_frameHeight};
 }

Player::~Player() {
    UnloadTexture(m_spriteSheet);
}

void Player::Update(float deltaTime) {
    PlayerState newState = PlayerState::IDLE;

    if (!m_dying) {
        int touchCount = GetTouchPointCount();
        if (touchCount == 0) {
            if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) {
                m_dashing = true;
            }

            if (m_tapTimer < DASH_ACTIVATED_DURATION) {
                m_tapTimer += deltaTime;
            }

            m_touching = false;
        } else {
            std::cout << GetTouchPosition(0).x << ' ' << GetTouchPosition(1).x << '\n';

            m_touching = true;

            for (int i = 0; i < touchCount; ++i) {
                Vector2 pos = GetTouchPosition(i);
                if (pos.x <= Config::SCREEN_WIDTH / 2) m_direction = Direction::Left;
                else m_direction = Direction::Right;
            }

            if (m_tapTimer < DASH_ACTIVATED_DURATION) {
                m_dashing = true;
                m_tapTimer = DASH_ACTIVATED_DURATION + 1;
            }
        }

        if (m_dashing) {
            newState = PlayerState::DASHING;
        } else if (IsKeyDown(KEY_LEFT)) {
            m_direction = Direction::Left;
            newState = PlayerState::WALKING;
        } else if (IsKeyDown(KEY_RIGHT)) {
            m_direction = Direction::Right;
            newState = PlayerState::WALKING;
        } else if (touchCount > 0) {
            newState = PlayerState::WALKING;
        } else {
            newState = PlayerState::IDLE;
        }
        
        switch (newState)
        {
            case PlayerState::DASHING:
                m_position.x += (m_direction == Direction::Right ? 1 : -1) * DASH_SPEED * deltaTime;

                m_dashTimer += deltaTime;
                if (m_dashTimer >= DASH_DURATION) {
                    m_dashTimer = 0.0f;
                    m_dashing = false;
                }
                break;

            case PlayerState::WALKING:
                m_position.x += (m_direction == Direction::Right ? 1 : -1) * WALK_SPEED * deltaTime;
                break;
            default:
                break;
        }
        clampToScreen();
    
        // laser collision
        if (m_hit && !m_isLifeDeducted){
            if (--m_life <= 0) {
                m_dying = true;
            }
            m_isLifeDeducted = true;
        }
    } else {
        newState = PlayerState::DYING;
    }

    // Texture
    m_frameCounter += deltaTime;
    if (m_oldState == newState) {
        if (m_frameCounter >= 1.0f / FRAME_SPEED) {
            m_frameCounter = 0;
            m_spriteFrame.x += m_frameWidth;

            if (m_dying && m_spriteFrame.x > m_frameWidth*4) {
                m_dead = true;
                m_spriteFrame.x = m_frameWidth*4;
            } 
        }
    } else {
        m_frameCounter = 0;
        m_spriteFrame.x = 0;
    }

    int frameCount;
    switch (newState) {
        case PlayerState::IDLE:
            m_spriteFrame.y = 0;
            frameCount = IDLE_FRAME_COUNT;
            break;
        case PlayerState::WALKING:
            m_spriteFrame.y = m_frameHeight;
            frameCount = WALKING_FRAME_COUNT;
            break;
        case PlayerState::DASHING:
            m_spriteFrame.y = m_frameHeight*2;
            frameCount = DASHING_FRAME_COUNT;
            break;
        case PlayerState::DYING:
            m_spriteFrame.y = m_frameHeight*3;
            frameCount = DYING_FRAME_COUNT;
            break;
    }
    m_spriteFrame.x = (int)m_spriteFrame.x % (m_frameWidth * frameCount);

    switch (m_direction) {
        case Direction::Left:   m_spriteFrame.width = -m_frameWidth; break;
        case Direction::Right:  m_spriteFrame.width = m_frameWidth; break;
    }

    m_oldState = newState;
}

void Player::Draw() const {
    // DrawRectangle(m_position.x - 24, m_position.y - 64, 48, 64, m_hit ? RED : WHITE);
    DrawTextureRec(m_spriteSheet, m_spriteFrame, {m_position.x - m_frameWidth/2, m_position.y - m_frameHeight}, m_hit ? RED : WHITE);
}

void Player::Move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
}

void Player::ResetHitFlags() {
    m_hit = false;
    m_isLifeDeducted = false;
}

void Player::TakeHit() {
    m_hit = true;
}

Rectangle Player::GetHitbox() const {
    return {m_position.x - 24, m_position.y - 64, 48, 64};
}

Vector2 Player::GetPosition() const {
    return m_position;
}

int Player::GetLivesLeft() const {
    return m_life;
}

bool Player::IsHit() const {
    return m_hit;
}

bool Player::isDead() const {
    return m_dead;
}

void Player::clampToScreen() {
    if (m_position.x - WIDTH/2 <= Config::SIDE_PADDING) m_position.x = Config::SIDE_PADDING + WIDTH/2;
    if (m_position.x + WIDTH/2 >= Config::SCREEN_WIDTH - Config::SIDE_PADDING) m_position.x = Config::SCREEN_WIDTH - Config::SIDE_PADDING - WIDTH/2;
}