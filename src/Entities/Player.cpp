#include "Player.h"

Player::Player() : 
    m_position({Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT - Config::UNIT_SIZE}),
    m_life(3),
    m_hit(false), 
    m_isLifeDeducted(false),
    m_oldState(PlayerState::IDLE),
    m_direction(Direction::Right),
    m_frameCounter(0),
    m_dashTimer(0.0f),
    m_dashing(false),
    m_dying(false) {

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

    if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT) || GetTouchPointCount() > 1) {
        m_dashing = true;
    }
    
    if (m_dashing) {
        newState = PlayerState::DASHING;
    } else if (IsKeyDown(KEY_LEFT)) {
        m_direction = Direction::Left;
        newState = PlayerState::WALKING;
    } else if (IsKeyDown(KEY_RIGHT)) {
        m_direction = Direction::Right;
        newState = PlayerState::WALKING;
    } else if (GetTouchPointCount() == 0) {
        // skip
    } else if (GetTouchPosition(0).x <= Config::SCREEN_WIDTH/2) {
        m_direction = Direction::Left;
        newState = PlayerState::WALKING;
    } else if (GetTouchPosition(0).x > Config::SCREEN_WIDTH/2) {
        m_direction = Direction::Right;
        newState = PlayerState::WALKING;
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
        m_life--;
        m_isLifeDeducted = true;
    }

    // Texture
    m_frameCounter += deltaTime;
    if (m_oldState == newState) {
        if (m_frameCounter >= 1.0f / FRAME_SPEED) {
            m_frameCounter = 0;
             m_spriteFrame.x += m_frameWidth;
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
    DrawRectangle(m_position.x - 24, m_position.y - 64, 48, 64, m_hit ? RED : WHITE);
    DrawTextureRec(m_spriteSheet, m_spriteFrame, {m_position.x - m_frameWidth/2, m_position.y - m_frameHeight}, WHITE);
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

void Player::clampToScreen() {
    if (m_position.x - WIDTH/2 <= Config::SIDE_PADDING) m_position.x = Config::SIDE_PADDING + WIDTH/2;
    if (m_position.x + WIDTH/2 >= Config::SCREEN_WIDTH - Config::SIDE_PADDING) m_position.x = Config::SCREEN_WIDTH - Config::SIDE_PADDING - WIDTH/2;
}